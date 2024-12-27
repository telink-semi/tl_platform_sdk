@page PWM_Example PWM

# PWM introduction

The SoC has 6 PWM channels: PWM0~PWM5.

The relevant modes supported by PWM are described as follows:

Modes supported by PWM0:

- continuous mode
- counting mode
- IR mode
- IR FIFO mode
- IR DMA FIFO mode

Modes supported by PWM1~PWM5:

- continuous mode

## Clock

The PWM clock source is available in two ways, either pclk or 32K, as shown below:

![Clock source for PWM](pic/clocksourceforpwm.png "Clock source for PWM")

**pclk:**

Function: The clock can be frequency divided and then the divided clock is used as the clock source for PWM.

Interface configuration: static inline void pwm_set_clk(unsigned char pwm_clk_div);

Where: pwm_clk_div = pclk_frequency /pwm_frequency -1; (pwm_clk_div: 0~255)

**32K:**

Function: The frequency division is not supported. It only supports continuous mode and counting mode. This configuration is mainly for the purpose of sending PWM waveforms even in suspend mode.

Interface configuration: static inline void pwm_32k_chn_en(pwm_clk_32k_en_chn_e pwm_32K_en_chn);

**Note:**

> - All channels use pclk clock source by default. If you want to use 32K clock source, call pwm_32k_chn_en to enable the corresponding channel, the channel that is not enabled still uses pclk clock source.
> - For 32K clock source, PWM design only considered when the suspend scenario, using interrupts in continuous mode and counting mode it will enter the interrupt a 32K clock cycle in advance, in this 32K clock cycle, it will exit the interrupt and enter the interrupt. When using 32K PWM, if you need interrupt, it is recommended using GPIO interrupt to achieve the interrupt.
> - When using 32K clock source, if you need to update the duty cycle during operation, only calling the function to set the duty cycle will not take effect, you should set the duty cycle and then call the following function before it will take effect.

The specific function interface is as follows:

```C
static inline void pwm_32k_chn_update_duty_cycle(void);
```

## Duty cycle

A signal frame of PWM consists of two parts, Count status (high level time) and Remaining status (low level time). And the specific waveform of a signal frame is as follows, where tmax is the cycle time.

![Specific waveforms of the signal frame](pic/specificwaveformsofthesignalframe.png "Specific waveforms of the signal frame")

The functions to set the signal frame period and duty cycle in the driver both use tcmp and tmax as parameters.

a) Generic function interface for setting duty cycle (all channels supported):

```C
static inline void pwm_set_tcmp(pwm_id_e id, unsigned short tcmp);
static inline void pwm_set_tmax(pwm_id_e id, unsigned short tmax);
```

**pwm_set_tcmp:**

id: select which PWM channel;

tcmp: set the high level duration.

**pwm_set_tmax:**

id: select which PWM channel;

tmax: set period.

**Note:**

> - The second parameter in the pwm_set_tmax function sets the period of PWM, the parameter type is short, the minimum value of tmax is 1 and cannot be 0. If tmax is 0, the pwm is in a non-working state, so the value of tmax is in the range of 1~65535.
> - The second parameter in the pwm_set_tcmp function sets the duty cycle of PWM, and the parameter type is short. The minimum value of tcmp can be 0, when it is 0, the waveform of pwm is always low, and the maximum value can be tmax, when the waveform of pwm is always high, so the value range of tcmp is: 0~tmax.

b) When using the IR FIFO Mode and IR DMA FIFO Mode of PWM0, another function interface will be used:

```C
static inline void pwm_set_pwm0_tcmp_and_tmax_shadow(unsigned short tmac_tick, unsigned short cmp_tick);
```

**Note:**

> - In the pwm_set_pwm0_tcmp_and_tmax_shadow function, the parameter tmac_tick sets the cycle of pwm0, and the parameter cmp_tick sets the high level duration of pwm0. The value range of tmac_tick: 1 \~ 65536, and the value range of cmp_tick: 0 \~ cycle_ tick.

c) When using the counting mode and IR mode of PWM0, pwm0 needs to set the number of pulses output function, using the following function interface:

```C
static inline void pwm_set_pwm0_pulse_num(unsigned short pulse_num);
```

pulse_num: the number of pulses.

d) When pwm0 writes cfg data to the fifo, the following function interface is used:

```C
static inline void pwm_set_pwm0_ir_fifo_cfg_data(unsigned short pulse_num, unsigned char use_shadow, unsigned char carrier_en);
```

**use_shadow:**

1: Use the period and duty cycle set under the pwm_set_pwm0_tcmp_and_tmax_shadow function.

0: Use the period and duty cycle set under pwm_set_tmax, pwm_set_tcmp function.

**carrier_en:**

1: Output pulse according to the settings of pulse_num and use_shadow.

0: Output low level, duration is calculated according to parameters pulse_num and use_shadow.

## Invert/polarity

(1) The waveform set by pwm_set_tcmp and pwm_set_tmax will output high level of Count status first and low level of Remaining status later by default.

(2) If PWM\*_PIN is used, the output waveform is the same as the waveform set by pwm_set_tcmp and pwm_set_tmax.

(3) If PWM\*_N_PIN is used, the output waveform is the opposite of PWM\*_PIN waveform.

(4) If the PWM\* channel invert function is enabled using pwm_invert_en, it will flip the PWM\*_PIN waveform.

(5) If the PWM\* channel invert function is enabled using pwm_n_invert_en, it will flip the PWM\*_N_PIN waveform.

(6) If the polarity function of PWM\* channels is enabled using pwm_set_polarity_en, all PWM_PINs will be output according to the following rule: Count status outputs low, Remaining status outputs high.

# Function description

## Continuous mode

This mode will keep sending signal at the set duty cycle, set stop if you want to stop, and stop immediately after setting. During sending, the duty cycle can be updated, and the duty cycle will take effect at the next frame.

## Counting Mode

It will stop once sending a set number of signal frames. In this mode, if stop, it will stop immediately. In this mode, modifying the duty cycle during sending will not change the duty cycle.

## IR Mode

It sends pulse groups continuously in IR mode, and the duty cycle can be changed in between and will take effect on the next pulse group. If you want to stop it immediately, you can stop it directly. The difference between IR mode and counting mode is that it sends one pulse group and then stops sending in counting mode, while it sends pulse groups continuously in IR mode.

If you want to stop IR mode and finish the current pulse group, you can switch to counting mode.

If you want to stop immediately, you can stop directly.

**Note:**

> - If you want to stop IR mode and finish the current pulse group, you can switch to counting mode in the interrupt, but during the switching process, the pulse group in the current IR mode will be sent out before switching over.

## IR FIFO mode

The long code pattern can be sent without the MCU intervention. The IR carrier frequency is obtained by dividing the system clock and can support common frequencies. The element "Fifo cfg data" is used as the base unit of the IR waveform, and the hardware will parse the cfg information to send the corresponding signal.

In the IR FIFO mode it takes out the cfg data in the FIFO in turn and sends the corresponding signal until the fifo is empty. In this mode, you can use stop, but it only stops the execution of the current cfg data and does not affect the execution of the cfg data after the fifo.

**Note:**

> - In IR FIFO mode, as long as the fifo has data, it will keep sending out (auto send), no start signal is needed, also IR DMA FIFO mode does not need start signal, but in all other modes, pwm_start signal is needed.
> - Every time the function pwm_set_pwm0_ir_fifo_cfg_data is called, the cnt of the FIFO is added by 1 (if the FIFO is full at this time, it waits until the FIFO is not full and then writes), and the hardware takes one out from the FIFO, the cnt in the FIFO is subtracted by 1. The depth of the FIFO is 8 bytes. After the data is taken out from the FIFO, the send signal action is executed, and only after the current signal is executed, the next one will be taken out from the FIFO.

## IR DMA FIFO mode

The IR DMA FIFO mode is similar to IR FIFO mode, except that the configuration is not written directly by the MCU in the FIFO, but is written to the FIFO via DMA.

**Note:**

> - Inside the interrupt you need to update the DMA part of the configuration: update of the source address, DMA triggering, and so on.
> - In this mode, unlike the IR FIFO, the interrupt is not triggered when the number of cfg data in the FIFO is empty, but only when all the configuration pwm signal frames in the fifo are executed.

# Interrupts

The interrupt settings supported by PWM are described as follows (hardware does not automatically clear the interrupt flag bit, it needs to be cleared manually by software).

**Interrupts supported by PWM0:**

a) FLD_PWM0_FRAME_DONE_IRQ: Each signal frame is completed and an interrupt is generated.

b) FLD_PWM0_PNUM_IRQ: An interrupt is generated after each pulse group is sent.

c) FLD_PWM0_IR_FIFO_IRQ: Enter interrupt when the cfg data inside the FIFO is less than (not including equal to) the set value (trigger_level).

d) FLD_PWM0_IR_DMA_FIFO_IRQ: When the FIFO has finished executing the cfg data sent by DMA, it enters the interrupt.

**Interrupts supported by PWM1:**

a) FLD_PWM1_FRAME_DONE_IRQ: Each signal frame is completed and an interrupt is generated.

**Interrupts supported by PWM2:**

a) FLD_PWM2_FRAME_DONE_IRQ: Each signal frame is completed and an interrupt is generated.

**Interrupts supported by PWM3:**

a) FLD_PWM3_FRAME_DONE_IRQ: Each signal frame is completed and an interrupt is generated.

**Interrupts supported by PWM4:**

a) FLD_PWM4_FRAME_DONE_IRQ: Each signal frame is completed and an interrupt is generated.

**Interrupts supported by PWM5:**

a) FLD_PWM5_FRAME_DONE_IRQ: Each signal frame is completed and an interrupt is generated.

A pulse group contains several frames and can be configured via the pwm_set_pwm0_pulse_num function interface:

```C
static inline void pwm_set_pwm0_pulse_num(unsigned short pulse_num).
```

The value of the IR FIFO mode trigger_level can be configured via the pwm_set_pwm0_ir_fifo_irq_trig_level function interface:

```C
static inline void pwm_set_pwm0_ir_fifo_irq_trig_level(unsigned char trig_level).
```

**Note:**

> - When responding to an interrupt, there is a time delay of about 2~4 us.

# Continuous mode

## Function description

The demo implements the following functions: LED1 will continuously send signal frame (high level time of 50us, period of 100us), at the same time, every time an interrupt is generated, LED4 will be toggled once (the GPIO is a marker signal set to do interrupt test).

## Example results

![Continuous mode test results](pic/continuousmodetestresults.png "Continuous mode test results")

The above figure shows the test results captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED4): is an interrupt marker GPIO, generating an interrupt for each signal frame sent.

The red box indicates: the time delay to generate the interrupt, the CPU needs a certain amount of software and hardware processing time to enter the interrupt.

## Other validation results

### Stop

Use the following test to verify that in continuous mode, signal will stop immediately after executing stop.

The code implementation is as follows, after the stop, toggle the state of LED3.

```C
pwm_start(PWM_ID);
delay_ms(1);
pwm_stop(PWM_ID);
gpio_toggle(LED3);
```

Test results are captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED3): is the stop marker GPIO.

As can be seen from the figure, the PWM signal stops immediately after LED3 is toggled.

![Other validation results](pic/othervalidationresults.png "Other validation results")

### Duty cycle

Use the following test to verify that in continuous mode, the duty cycle can be updated during the data sending period, and the update of the duty cycle will take effect in the next frame. The code implementation is as follows, after modifying the duty cycle state, the state of LED3 is toggled.

```C
pwm_start(PWM_ID);
delay_ms(1);
pwm_set_tcmp(PWM_ID,10 * CLOCK_PWM_CLOCK_1US);
gpio_toggle(LED3);
```

Test results are captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED3): is the duty cycle update marker GPIO.

As can be seen from the figure, after LED3 is toggled, PWM modifies the duty cycle to take effect at the next frame.

![Update duty cycle](pic/updatedutycycle.png "Update duty cycle")

# Counting mode

Choose which interrupt method by using the macro in app_pwm_count.c

```C
#define COUNT_FRAME_INIT 1
#define COUNT_PNUM_INIT 2
#define SET_COUNT_INIT_MODE COUNT_FRAME_INIT
```

## COUNT_FRAME_INIT

### Function description

The demo implements the following functions, LED1 will output a number of 16 signal frame (high level time of 50us, period of 100us), at the same time, it generates an interrupt every signal frame sent, , LED4 will be toggled once (the GPIO is a marker signal set to do interrupt test).

### Example results

![COUNT_FRAME_INIT example](pic/countframeinitexample.png "COUNT_FRAME_INIT example")

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED4): is an interrupt marker GPIO, generating an interrupt for each signal frame sent.

The red box indicates: the time delay to generate the interrupt, the CPU needs a certain amount of software and hardware processing time to enter the interrupt.

## COUNT_PNUM_INIT

### Function description

The demo implements the following functions: LED1 will output a signal frame with a number of 16 (50us high level time, 100us period), and after sending the specified number of pulses, an interrupt will be generated and LED4 will be toggled (the GPIO is a marker signal set for interrupt testing).

### Example results

![COUNT_PNUM_INIT example](pic/countpnuminitexample.png "COUNT_PNUM_INIT example")

The details of the red boxes are as follows:

![Details of the red boxes](pic/detailsoftheredboxes.png "Details of the red boxes")

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED4): is the interrupt marker GPIO, specify the number of pulses sent out, generate an interrupt.

Red box description: 3us more than 50us, indicating that there is a certain time delay to enter the interrupt and the CPU needs a certain amount of software and hardware processing time to enter the interrupt.

## Other validation results

### Stop

Use the following test to verify that in counting mode, signal will stop immediately after executing stop.

The code implementation is as follows, after the stop, toggle the state of LED3.

```C
pwm_start(PWM_ID);
delay_ms(1);
pwm_stop(PWM_ID);
gpio_toggle(LED3);
```

Test results are captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED3): is the stop marker GPIO.

As can be seen from the figure, the PWM signal stops immediately after LED3 is toggled.

![Other validation results](pic/othervalidationresults1.png "Other validation results")

### Duty cycle

Use the following test to verify that in counting mode, the duty cycle cannot be changed when changing the duty cycle during data sending.

The code is implemented as follows, toggle the state of LED3 after modifying the duty cycle state.

```C
pwm_start(PWM_ID);
delay_ms(1);
pwm_set_tcmp(PWM_ID,10 * CLOCK_PWM_CLOCK_1US);
gpio_toggle(LED3);
```

Test results are captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED3): is the duty cycle update marker GPIO.

As can be seen from the figure, the signal of PWM does not change after LED3 is toggled.

The test results are as follows:

![Changing duty cycle](pic/changingdutycycle.png "Changing duty cycle")

# IR mode

## Function description

The demo implements the following functions, LED1 will output 6 pulse groups (each pulse group, the number of pulses is 4, the high level time is 50us, the period is 100us), at the same time, after sending a pulse group, an interrupt is generated, LED4 will be toggled once (the GPIO is a marker signal set to do interrupt test).

## Example results

![IR mode example](pic/irmodeexample.png "IR mode example")

The above figure shows the test results captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED3): is an interrupt marker GPIO, toggle once after a pulse group sent.

The red box indicates: the time delay to generate the interrupt, the CPU needs a certain amount of software and hardware processing time to enter the interrupt.

## Other validation results

### Stop

Use the following test to verify that in counting mode, signal will stop immediately after executing stop.

The code implementation is as follows, after the stop, toggle the state of LED3.

```C
pwm_start(PWM_ID);
delay_ms(1);
pwm_stop(PWM_ID);
gpio_toggle(LED3);
```

Test results captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED3): is the stop marker GPIO.

As can be seen from the figure, the PWM signal stops immediately after LED3 is toggled.

![Other validation results](pic/othervalidationresults2.png "Other validation results")

### Duty cycle

Use the following test to verify that in counting mode, the duty cycle can be changed in the middle, but it will take effect after the current pulse group is executed.

The code implementation is as follows:

```C
pwm_start(PWM_ID);
delay_ms(1);
pwm_set_tcmp(PWM_ID,10 * CLOCK_PWM_CLOCK_1US);
gpio_toggle(LED3);
```

Test results are captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED3): is the duty cycle update marker GPIO.

As you can see from the figure, the signal of pwm does not change immediately after LED3 is toggled, but takes effect after the current pulse group is executed.

![Changing duty cycle](pic/changingdutycycle1.png "Changing duty cycle")

# IR FIFO Mode

## Function description

The general flow of the IR FIFO MODE demo is introduced: at the beginning, write two groups of cfg data1, cfg data2 to the FIFO, when the cfg data inside the FIFO is less than (not including equal to) the set value (trigger_level is 1) to enter the interrupt, in the interrupt the same two groups of cfg data1, cfg data2 are configured.

The demo implements the following functions, LED1 is sent in two groups of pulses in sequence and continuously, and the two groups of pulses are set as follows:

(1) cfg data1, high level time of 50us, period of 100us

(2) cfg data2, high level time of 100us, period of 200us

LED4 will be toggled once for each interrupt generated (this GPIO is a marker signal set to do interrupt testing).

## Example results

![IR FIFO mode example](pic/irfifomodeexample.png "IR FIFO mode example")

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED4): is the interrupt marker GPIO, when the cfg data inside the FIFO is less than (not including equal to) the set value (trigger_level is 1), toggle once (after the execution of cfg data1, cfg data2 is taken out from the FIFO, the value of cnt is 0, which is less than the trigger level (value is 1), it enters an interrupt).

The red box indicates: the time delay to generate the interrupt, the CPU needs a certain amount of software and hardware processing time to enter the interrupt.

## Other validation results

### Stop

Use the following test to verify that in IR FIFO mode, after executing stop, it only stops the execution of the current cfg data and does not affect the execution of the cfg data after the fifo.

The code implementation is as follows, after the stop, toggle the state of LED3.

```C
delay_ms(10);
pwm_stop(PWM_ID);
gpio_toggle(LED3);
```

Test results are captured using a logic analyzer:

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED3): is the stop marker GPIO.

In the IR FIFO MODE function description:

cfg data1: Number of pulses is 5, high level time is 50us, period is 100us.

cfg data2: number of pulses is 6, high level time is 100us, period is 200us.

As can be seen from the figure, after executing stop, LED3 is toggled, stopping the execution of the current cfg data1 does not affect the execution of cfg data2 behind the fifo.

![Other validation results](pic/othervalidationresults3.png "Other validation results")

# DMA FIFO mode

Select the working method by using the macro in app_pwm_ir_dma.c

```C
#define 	PWM_IR_FIFO_DMA 	1
#define 	PWM_CHAIN_DMA 		2
#define     SET_PWM_DMA_MODE 	PWM_IR_FIFO_DMA
```

## PWM_IR_FIFO_DMA

In IR DAM FIFO Mode, interrupts need to be constantly triggered to request DMA to send cfg data to the FIFO.

IR DMA FIFO Mode program rough flow: in the main program through the DMA request, send three groups of cfg data to the FIFO, respectively cfg data1, cfg data2, and cfg data3. When all the cfg data in the FIFO are executed, enter the interrupt, in the interrupt through the DMA request, send two groups of cfg data to the FIFO, respectively cfg data4, cfg data5.

### Function description

The demo implements the following functions, with LED1 sending a three-set of pulse group at the beginning:

cfg data1: the number of pulses is 5, the high level time is 50us, and the period is 100us.

cfg data2: the number of pulses is 4, the high level time is 50us, and the period is 100us.

cfg data3: the number of pulses is 6, the high level time is 100us, and the period is 200us.

Next, two sets of pulses are continuously sent in groups of two pulses:

cfg data4: the number of pulses is 4, the high level time is 50us, and the period is 100us

cfg data5: the number of pulses is 4, the high level time is 50us, and the period is 100us

At the same time, LED4 will be toggled once for each interrupt generated (this GPIO is a marker signal set to do interrupt testing).

### Example results

![PWM_IR_FIFO_DMA example](pic/pwmirfifodmaexample.png "PWM_IR_FIFO_DMA example")

Channel 0 (LED1): is the PWM output signal.

Channel 1 (LED4): is the interrupt marker GPIO.

As you can see from the above figure, in this mode, the interrupt is triggered only when all the cfg data of the FIFO is executed, which is different from the interrupt mechanism of IR FIFO Mode.

The following figure is the enlarged red box in the above figure. From the figure, we can see that the last low maintenance time of cfg data3 is 105us (not 100us as set by cfg data3), so we can see that in this usage method, after sending the first group of DMA data, the DMA is retriggered in the interrupt, and there is a time delay on the signal. (This example is equivalent to the actual output: cfg1+cfg2+cfg3+delay(low level 5us or so)+cfg4+cfg5), the 5us time includes the time to enter the interrupt and reset the relevant settings.

![Zoom box of PWM_IR_FIFO_DMA example](pic/zoomboxofpwmirfifodmaexample.png "Zoom box of PWM_IR_FIFO_DMA example")

## PWM_CHAIN_DMA

The SoC chip's DMA has a chain table form that can be used in conjunction with the DMA FIFO mode, the advantage of which is that it is possible to keep sending the desired signal repeatedly without the MCU's intervention. In the previous IR DAM FIFO Mode example, it is necessary to continuously trigger interrupts to request DMA to send cfg data to the FIFO, using the chain table method can also accomplish the function of continuous sending data without interrupt participation.

In the example of pwm_chain_dma, the chain table structure is as follows:

![PWM_CHAIN_DMA chain table structure](pic/pwmchaindmachaintablestructure.png "PWM_CHAIN_DMA chain table structure")

First create the head node head_of_list , then add nodes to the circular chain table, in the demo, two circular chain table nodes are added, tx_dma_list[0] and tx_dma_list[1].

**Note:**

> - The head node needs to be configured with the DMA source address, the DMA length, and the address where the next node configuration is located. We cannot just configure the address where the next node configuration is located.

From the flow chart, we can see that the execution of the head pointer starts first, then tx_dma_list[0], tx_dma_list[1], then tx_dma_list[0] is executed, and so on in a loop until LLP is set to 0.

This is only to achieve two circular chain tables through DMA to achieve continuous sending. If you want to achieve more arrays of circular sending, you can follow the above structure to add the corresponding pointer structure.

The specific DMA chain table configuration is as follows:

```C
pwm_set_dma_config(DMA_CHN);
pwm_set_dma_chain_llp(DMA_CHN,(u16*)(&CHIAN_DMA_Buff[0]),MIC_BUFFER_SIZE,&tx_dma_list[0]);
pwm_set_tx_dma_add_list_element(DMA_CHN,&tx_dma_list[0],&tx_dma_list[1],(u16*)(&CHIAN_DMA_Buff[0]),CHAIN_BUFFER_SIZE);
pwm_set_tx_dma_add_list_element(DMA_CHN,&tx_dma_list[1],&tx_dma_list[0],(u16*)(&CHIAN_DMA_Buff[1]),CHAIN_BUFFER_SIZE)
pwm_ir_dma_mode_start(DMA_CHN);
```

The DMA chain table differs from PWM_IR_FIFO_DMA in that:

pwm_set_dma_chain_llp function and pwm_set_tx_dma_add_list_element function.

Set the chain table header with the pwm_set_dma_chain_llp function.

```C
void pwm_set_dma_chain_llp(dma_chn_e chn,u16 * src_addr, u32 data_len,dma_chian_config_t * head_of_list)
```

chn: DMA configuration.

src_addr: DMA source address, that is cfg data array.

data_len: DMA data length.

head_of_list: the address where the next node is configured.

Contents included in each node: DMA configuration, address where the current node configuration is located, address where the next node configuration is located, DMA source address, DMA length, nodes of the circular chain table set by the pwm_set_tx_dma_add_list_element function.

```C
void pwm_set_tx_dma_add_list_element(dma_chn_e chn, dma_chian_config_t *config_addr, dma_chian_config_t *llponit , u16 * src_addr, u32 data_len)
```

chn : DMA configuration.

config_addr: The address where the current node configuration is located.

llponit: The address where the next node configuration is located.

src_addr: DMA source address, that is cfg data array.

data_len: DMA data length.

### Function description

The demo implements the following functions, LED1 will first send the cfg data array configured by the head node at the beginning, and then will execute non-stop sending the cfg data array configured by node 1 and the cfg data array configured by node 2 alternately and circularly.

Node 1 is configured with the following cfg data:

cfg data1: the number of pulses is 5, the high level time is 100us, and the period is 200us.

cfg data2: the number of pulses is 4, the high level time is 100us, and the period is 200us.

cfg data3: the number of pulses is 6, the high level time is 100us, and the period is 200us.

cfg data4: the number of pulses is 3, the high level time is 100us, and the period is 200us.

 Node 2 is configured with the following cfg data:

cfg data 5: the number of pulses is 5, the high level time is 50us, and the period is 100us.

cfg data6: the number of pulses is 4, the high level time is 50us, and the period is 100us.

cfg data7: the number of pulses is 6, the high level time is 50us, and the period is 100us.

cfg data8: the number of pulses is 3, the high level time is 50us, and the period is 100us.

## Example results

![PWM_CHAIN_DMA example](pic/pwmchaindmaexample.png "PWM_CHAIN_DMA example")

Channel 0 (LED1): is the PWM output signal.

To elaborate on the red box, the cfg data of pointer 1 and pointer 2 are switched without the generation of time delay.

![Details of the red boxes 1](pic/detailsoftheredboxes1.png "Details of the red boxes 1")

![Details of the red boxes 2](pic/detailsoftheredboxes2.png "Details of the red boxes 2")

As can be seen from the figure, there is no delay generation, so a continuous PWM waveform can be sent using the chain table approach.

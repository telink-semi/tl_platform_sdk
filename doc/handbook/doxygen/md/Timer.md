@page Timer_Example TIMER


This SoC supports 2 timers: Timer0 and Timer1.

The following four modes are supported: System Clock Mode, GPIO Trigger Mode, GPIO Pulse Width Mode, and Tick Mode.

There is also a watchdog timer, configured as "watchdog" to monitor system operation and reboot if there is an exception.

# Function description

When using Timer0, Timer1 timers, you need to specify which mode to use by setting the timer_set_mode function interface:

```C
void timer_set_mode(timer_type_e type, timer_mode_e mode,unsigned int init_tick, unsigned int cap_tick).
```

When using GPIO Trigger Mode and GPIO Pulse Width Mode of Timer0 and Timer1, the clock source of Timer is provided by GPIO, which needs to be set through the following interface. You can select GPIO and polarity, and the corresponding GPIO interrupt mask will also be set in this interface, so that the timer interrupt can be generated normally.

```C
void timer_gpio_init(timer_type_e type, gpio_pin_e pin, gpio_pol_e pol ).
```

## System Clock Mode

---------------------------------------------------------------------------
Clock Source   Function                     Mechanism Description
-------------- ---------------------------- ---------------------------------------------------
pclk           Timed interrupt generation   After setting to this mode, when a rising edge of pclk is detected, count register of the timer will add 1 until reaching the capture value, generating an interrupt, and at the same time, initial_tick will be automatically loaded, and recounted, and when reaching capture value, the interrupt will be entered again, timer enable is not turned off, so that this operation will be cyclic all the time.

---------------------------------------------------------------------------

Setup steps (as the following code):

```C
timer_set_mode(TIMER0, TIMER_MODE_SYSCLK, 0, 50*sys_clk.pclk*1000);
timer_start(TIMER0);
```

## GPIO Trigger Mode

--------------------------------------------------------------------------------------------------------------------------------------
Clock Source      Function                                                         Mechanism Description
----------------- ---------------------------------------------------------------- ---------------------------------------------------
Provided by GPIO  Specific number of GPIO rising/falling edge triggers interrupts. After setting to this mode, the timer will count plus 1 for every rising/falling edge of GPIO. When the timer count value reaches the specified set number, an interrupt will be performed, the timer will be cleared to start counting again. The timer enable interrupt is not turned off, so that the operation will be cyclic all the time.

--------------------------------------------------------------------------------------------------------------------------------------

Setup steps (as the following code):

```C
timer_gpio_init(TIMER0, SW1,POL_RISING);
timer_set_mode(TIMER0, TIMER_MODE_GPIO_TRIGGER,0,TIMER_MODE_GPIO_TRIGGER_TICK);
timer_start(TIMER0);
```

## GPIO Pulse Width Mode

----------------------------------------------------------------------------------------
Clock Source   Function              Mechanism Description
-------------- --------------------- ---------------------------------------------------
pclk           Capture pulse width   After setting to this mode, if the set GPIO detects a rising/falling edge, it will trigger the timer timing. For every pclk, the timer will count plus 1. When the GPIO level invert is detected, it will enter the interrupt, the timer count stops, at this time the current tick count value can be read to calculate the width of the GPIO pulse. This interrupt is triggered once, will not operate in automatic loop.

----------------------------------------------------------------------------------------

Setup steps (as the following code):

```C
timer_gpio_init(TIMER0, SW1, POL_FALLING);
timer_set_mode(TIMER0, TIMER_MODE_GPIO_WIDTH,0,0);
timer_start(TIMER0);
```

Example: If the polarity is set to POL_FALLING, the timing is triggered at the falling edge and the interrupt is generated at the rising edge.

## Tick Mode

-------------------------------------------------------------------------------------------------------------------------------------------
Clock Source        Function                                          Mechanism Description
------------------- ------------------------------------------------- ---------------------------------------------------------------------
pclk                Can be used as a time indicator,                  After setting to this mode, the timer will count plus 1 for every rising/falling
                    this mode does not generate interrupt.            edge of GPIO. When the timer count value reaches the specified set number,
                                                                      an interrupt will be performed, the timer will be cleared to start counting again. If the initial count value of the timer is not set to 0 at the specified time, then the timer will keep adding 1 until the timer count overflows, automatically setting the initial count value of the timer to 0 and starting the timer again, and the timer will keep cycling through the timer like a clock.

-------------------------------------------------------------------------------------------------------------------------------------------

Setup steps (as the following code):

```C
timer_set_mode(TIMER0, TIMER_MODE_TICK,0,0);
timer_start(TIMER0);
```

## Watchdog Mode

--------------------------------------------------------------------------------------------------------------------------------------------
Clock Source        Function                                                 Mechanism Description
------------------- -------------------------------------------------------- ---------------------------------------------------------------
pclk                Reset if you do not "feed the dog" within the set time   After setting to this mode, the watchdog starts timing. If the dog is not fed within the specified time, the program will reset. The dog feeding function is: wd_clear_cnt, this function will clear the timing and restart the timing. If the watchdog is not used, you need to turn off the watchdog to avoid the program reset.

--------------------------------------------------------------------------------------------------------------------------------------------

Setup steps (as the following code):

```C
wd_set_interval_ms(1000,sys_clk.pclk*1000);
wd_start();
```

# Demo description

Choose which mode to use using the macro TIMER_MODE in Timer_Demo/app_config.h.

```C
#define TIMER_SYS_CLOCK_MODE      1
#define TIMER_GPIO_TRIGGER_MODE   2
#define TIMER_GPIO_WIDTH_MODE     3
```

## GPIO System Clock Mode

**Demo setting:**

Timer0, set to system clock mode, set initial_tick=0, capture value=50ms, enable timer0. Interrupt will be reversed using LED2.

**Execution result:**

LED2 will be reversed every 50ms, resulting in the following:

Channel 1 (LED2): is an interrupt marker GPIO, about 50ms, reversing once.

![GPIO System Clock Mode](pic/gpiosystemclockmode.png "GPIO System Clock Mode")

## GPIO Trigger Mode

**Demo setting:**

Timer0, set to GPIO trigger mode, initialize GPIO, configure SW1 as timer0s clock source, trigger at rising edge, set initial_tick=0, value=0xf, enable timer0. Interconnect GPIO_PA2 and SW1 pins, GPIO_PA2 generates a rising edge every 500ms, when reaching the capture value, it enters an interrupt. The interrupt will be reversed using GPIO_PB5.

**Execution result:**

For every 15 rising edges generated by GPIO_PA2, LED2 reverses once, resulting in the following:

Channel 1 (LED2): is the interrupt marker GPIO, for every 15 rising edges generated by GPIO_PA2, LED2 generates a reverse.

Channel 0 (GPIO_PA2): is the trigger signal pin GPIO_PA2.

![GPIO Trigger Mode](pic/gpiotriggermode.png "GPIO Trigger Mode")

The following is detailed description of the red box:

![Red box 1](pic/redbox1.png "Red box 1")

![Red box 2](pic/redbox2.png "Red box 2")

As you can see from the red box 1 and 2, after the 15th rising edge of the previous interrupt, the delay is about 4.25us, it will enter the current interrupt, and LED2 will be reversed. And after the current LED2 lasts for 15 rising edges, the delay is about 4.25us and it will enter the next interrupt.

## GPIO Pulse Width Mode

**Demo setting:**

Timer0, set to GPIO pulse width mode, initialize GPIO, configure SW1 as trigger source for timer0, trigger at falling edge, set initial_tick=0, capture value=0, enable timer0. Interconnect GPIO_PA2 and SW1 pins, GPIO_PA2 generates a falling edge, trigger timer timing, delay 250ms, GPIO_PA2 generate a rising edge, it enters an interrupt. The interrupt will be reversed using LED2.

**Execution result:**

When GPIO_PA2 generates a rising edge, LED2 reverses and the result is as follows:

Channel 0 (GPIO_PB4): is the waveform of trigger source GPIO_PA2.

Channel 1 (LED2): is an interrupt marker GPIO, detects that GPIO_PA2 generates a rising edge, an interrupt occurs, and LED2 generates a reverse.

![GPIO Pulse Width Mode](pic/gpiopulsewidthmode.png "GPIO Pulse Width Mode")

![Red box description](pic/redboxdescription.png "Red box description")

The time delay for generating interrupts is 4.75us, and the CPU entering the interrupt needs a certain amount of software and hardware processing time.

Reading the timing register of the timer results in the following:

![Timing register](pic/timingregister.png "Timing register")

For 0x005b8e01 hexadecimal conversion to decimal, the result is 6000129, using the system clock, the frequency is 24M, every 1/24M seconds count once, 6000129 * (1/24M) calculated to be about 250ms.

## Tick Mode

**Demo setting:**

Timer0, set to tick mode, set initial_tick=0, capture value=0, enable timer0. Every 500ms, manually set the timer timing to start from the beginning and LED2 reverses once.

**Execution result:**

LED2 will be reversed every 500ms, resulting in the following:

Channel 1 (LED2): is tick mode marker GPIO, which is reversed once every 500ms or so.

![Tick Mode](pic/tickmode.png "Tick Mode")

## Watchdog Mode

### Dog-feeding test

**Demo setting:**

Set the watchdog time, reg_wt_target=1000ms. Every 990ms, feed the dog and LED2 reverses once.

**Execution result:**

LED2 will be reversed every 990ms, resulting in the following:

Channel 1 (LED2): is the dog-feeding test marker GPIO, which is reversed every 990ms or so.

![Dog feeding test](pic/dogfeedingtest.png "Dog feeding test")

### No dog-feeding test

If the dog is not fed within the set watchdog time.

**Demo setting:**

delay_ms(990);

//wd_clear_cnt(); //cancel the dog feeding operation

gpio_toggle(LED2);

**Execution result:**

LED2 will periodically output a waveform with a low level of 991.3847ms and a high level of 10.0074ms, resulting in the following:

Channel 1 (LED2): is no dog-feeding test marker GPIO.

![No dog-feeding test](pic/nodogfeedingtest1.png "No dog-feeding test")

![No dog-feeding test](pic/nodogfeedingtest2.png "No dog-feeding test")

Result: The time set for watchdog is 1000ms, after 990ms delay, reverse LED2, as there is no dog feeding, LED2 high level state is maintained for 10ms, after reaching the time set for watchdog, the program resets and keeps repeating the above operation.

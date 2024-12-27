@page PM_Example PM

The MCU is in working mode during normal program execution and the current will be at the mA level. If you need to save power you need to enter the low power mode.

# Function description

The Low power mode (LPM), also known as sleep mode, has three types as follows:

(1) Suspend

(2) deep sleep without SRAM retention (hereinafter referred to as deep)

(3) deep sleep with SRAM retention (hereinafter referred to as deep retention)

Each mode is divided into PAD wake-up, 32k_timer wake-up (internal 32k, external 32k clock source), MDEC wake-up, LPC wake-up and CORE wake-up depending on the wake-up source, where CORE wake-up only supports suspend mode and other wake-up sources support all modes.

The current chip models that support deep retention mode include: blackHawk (8K), kite (8K/16k/32k), vulture (16k/32k), and eagle (32k/64k).

The states of SRAM, digital register, and analog register in the three low-power modes are as follows.

|module|suspend|deep retention|deep|
|:--------:|:--------:|:--------:|:--------:|
|SRAM|100% keep|First 16K/32K/64K keep, others lost|100% lost|
|digital register|99% keep|100% lost|100% lost|
|analog register|100% keep|99% lost|99% lost|

The three low-power modes are described as follows:

## Suspend

In suspend mode, the program stops running, similar to a pause function. When the suspend mode is woken up, the program continues to execute. In suspend mode, the PM module works normally, SRAM does not power down (no data loss), all the analog register does not power down, and a small amount of digital register power down. In order to save power, the software can be set to power down the RF/USB/Audio modules, at this time the corresponding part of the digital register of these modules will be lost. For example, RF needs to be re-initialized after waking up in order to send packets, the rest of the registers are not lost. If you want to be able to send packets directly after waking up, you cannot set the corresponding module power down, but the corresponding power consumption will increase. It can be woken up by IO, timer, and other methods; here it should be noted that in the pad wake-up mode in order to avoid false triggering, you need to do the corresponding pull-up and pull-down to ensure the initial level.

## Deep

In deep mode, the program stops running, the vast majority of the MCU hardware modules are powered off. When the deep mode is woken up, the MCU will restart, similar to re-powering, and the program starts initializing again. In deep mode, the pm module works normally, the SRAM is powered down, data is lost, most of the 3.3V analog register will be saved, the rest of the analog register is powered down, and all digital registers are powered down. It can be woken up by IO, Timer, and other methods, but the SRAM data is lost.

## Deep retention

The deep mode has low current, but cannot store SRAM information; the suspend mode can keep SRAM and register without losing data, but the current is high. In order to achieve some application scenarios that require low current when sleeping and to ensure that the state can be restored immediately after waking up from sleep, the deep retention mode is added. The Deep Retention mode is closer to deep mode, and the only difference with deep is that it can save SRAM, and you can choose the size of SRAM retention area according to your actual needs.

In deep retention mode, the program stops running, most of the MCU hardware modules are powered off. When the deep retention mode is woken up, the MCU will restart, similar to re-powering, the program starts initialization again. In deep retention mode, pm module works normally, SRAM keeps part of the space without power off, the rest is powered off. All others are powered down, most of the 3.3V analog register will be saved, other analog register is powered down, all digital register is powered down, and the current value greater than deep mode is the current value consumed to keep the SRAM. It can be woken up by IO, Timer, and other methods. Since deep retention mode will save SRAM, it can save part of the action of moving code/data from flash to RAM after waking up. In addition, the program can also define the retention data. The variable defined as retention data will not go to flash to get the value after waking up, but will be saved in SRAM directly, so the last modified value will be saved.

## Low power mode workflow

The MCU operation flow is different for different sleep modes. The following is a detailed description of the MCU operation flow after waking up from the 3 sleep modes: suspend, deepsleep, and deepsleep retention. Please refer to the following diagram.

![MCU operation flow](pic/mcuoperationflow.png "MCU operation flow")

**Description of the modules in the flowchart.**

a) Run hardware bootloader

The MCU hardware performs some fixed actions that are solidified in the hardware and cannot be modified by software.

b) Run software bootloader

After the hardware bootloader finishes running, the MCU starts running the software bootloader, which is the vector segment that corresponds to the assembly program inside the S file. The software bootloader is to set up the memory environment for the later C program, which can be understood as the initialization of the whole memory.

c) System initialization

The system initialization corresponds to the initialization of each hardware module such as sys_init and clock_init in the main function, and sets the digital/analog register status of each hardware module.

d) User initialization

The user initialization corresponds to the function user_init.

e) main_loop

After the user initialization is completed, it enters the main_loop controlled by while(1). The series of operations before entering sleep mode in main_loop is called "Operation Set A", and the series of operations after waking up from sleep is called "Operation Set B".

**Process analysis of each sleep mode.**

(1) no sleep

Without sleep, the MCU runs as a loop in while(1), repeatedly executing "Operation Set A" -> "Operation Set B".

(2) suspend

The cpu_sleep_wakeup function is called to enter the suspend mode. When the suspend mode is woken up, the MCU continues to run to "Operation Set B", similar to the normal exit of the cpu_sleep_wakeup function. During suspend sleep, all SRAM data remains unchanged, and most of the digital/analog register states remain unchanged (with a few special exceptions); therefore, after the suspend mode is woken up, the program continues to run in its original position, and there is almost no need to consider any SRAM and register state recovery.

(3) deepsleep

The cpu_sleep_wakeup function is called to enter the deep mode, and when the deep mode is woken up, similar to re-powering, the MCU goes back to hardware bootloader to run again. During deep sleep all SRAM and most of the digital/analog registers are powered down (with the exception of some special analog registers) and all hardware and software initialization will be redone.

(4) deepsleep retention

The deep retention mode is a sleep mode between suspend and deep. The cpu_sleep_wakeup function is called to enter deep retention mode. When deep retention is woken up, the MCU returns to run software bootloader to start running. During the deep retention sleep period SRAM keeps only a part of SRAM powered on, most of the digital/analog registers are powered down (with the exception of some special analog registers). After waking up, part of the data in front of the SRAM is kept, and the step of "Run hardware bootloader" can be skipped, because the retention area on the SRAM is limited, "run software bootloader" cannot be skipped and must be executed; because deepsleep retention cannot save the register state, the system initialization must be executed and the register initialization needs to be reset. Since the program can also define the retention data, the user initialization can be optimized and improved, and the user initialization after power on/deep wake-up can be differentiated.

# Driver description

The driver layer provides a number of interface resources for use by the upper application layer, which are described below.

## Reserved information BUF

When the chip enters the deep/retention state, the data of most of the registers will be lost. The chip reserves 8 registers that will not be lost in deep/retention, so that the application layer can record some information that you want to save in the sleep state. You can define in the driver as the following (0x38<0> and 0x39<0> are used by the driver and the rest is reserved for the application layer):

(1) The following registers will be cleared in three cases: watchdog, hardware/software reset, and power-up.

```C
//watchdog, chip reset, RESET Pin, power cycle
#define PM_ANA_REG_WD_CLR_BUF0     0x38 // initial value 0xff. [Bit0] is already occupied. The customer cannot change!
```

(2) The following registers will be cleared only when re-powered.

```C
#define PM_ANA_REG_POWER_ON_CLR_BUF0   0x39 // initial value 0x00. [Bit0] is already occupied. The customer cannot change!
#define PM_ANA_REG_POWER_ON_CLR_BUF1   0x3a // initial value 0x00
#define PM_ANA_REG_POWER_ON_CLR_BUF2   0x3b // initial value 0x00
#define PM_ANA_REG_POWER_ON_CLR_BUF3   0x3c // initial value 0x00
#define PM_ANA_REG_POWER_ON_CLR_BUF4   0x3d // initial value 0x00
#define PM_ANA_REG_POWER_ON_CLR_BUF5   0x3e // initial value 0x00
#define PM_ANA_REG_POWER_ON_CLR_BUF60x3f // initial value 0x0f
```

## Status information

The driver defines a global variable g_pm_status_info that will update the relevant status of the pm in the **sys_init** function, which contains the following:

```C
typedef struct{
    unsigned char is_pad_wakeup;  //Whether this time it is woken up by the pad
    unsigned char wakeup_src; //Which wake-up source is for wake-up this time, including the wake-up status of PAD, TIMER, MDEC, LPC and CORE.
    pm_mcu_status mcu_status; //Which state is MCU back from, including power on/watchdog/deep/deep ret four states
    unsigned char rsvd;
}pm_status_info_s;

extern _attribute_aligned_(4) pm_status_info_s g_pm_status_info;
```

**Note:**

> - For the wake-up source WAKEUP_STATUS_TIMER, as long as the timer time to the set time, the flag will be set up by itself, even if no timer wake-up set on, the flag will be set up, but not wake-up. After clearing the flag, it will still be set up when the time comes.
> - For the wake-up source WAKEUP_STATUS_CORE, it belongs to the digital part of the wake-up mode, during the wake-up process the digital registers can not be powered off, so it only supports suspend sleep mode. Register configuration default open core wake-up, when power on/deep/deep ret is back the wake-up source flag bit will be set up, you need to ignore this flag bit, back from suspend the wake-up source flag bit  will display normally.
> - For the wake-up source WAKEUP_STATUS_PAD, when entering sleep, if the pad meets the wake-up condition, the program will not enter sleep and continue to run. If it is deep mode, the driver sleep function is set to enter reboot, and the program is processed as reboot. If it is retention mode, the driver sleep function is not processed, the upper software can be processed as suspend, and after exiting the sleep function, the rf module needs to be initialized again.

## Suspend power setting

Interface function: pm_set_suspend_power_cfg

This function configures whether the basebend, usb, and npe modules are powered down when suspend. The default state is all power down. If you want to be in suspend mode, you can call this function to set it before entering suspend.

## LPC wake-up

In the test, it is found that when setting 872mv and 50%, it can wake up below 2.02V (normally it should wake up below 1.744V), the reason is that the LPC function is less accurate in LPC_LOWPOWER mode.

## USB wake-up

In the test, we found that the USB wake-up flag will be set wrongly, because the trigger condition of USB wake-up is that there is a voltage change on the USB pins DP and DM and data is generated, before setting the USB wake-up, software configuration is needed to connect the DP pin to pull-up and the DM pin to pull-down, which can ensure the stability of the voltage level.

**Note:**

> - The DM pin is connected to the pull-down in order to simulate the state of the connection with the host, which is only needed when testing the USB wake-up configuration.

# Demo description

## Process description

The flow chart of the Demo is as follows.

![Demo flow chart](pic/demoflowchart.png "Demo flow chart")

**Flowchart description:**

(1) The 2s delay is added at the beginning to keep communication possible, because after entering sleep, swire will not work, it is easy to fail active when using BDT and cannot burn the program.

(2) Turn off all IO pins to prevent leakage before the current test starts.

(3) CORE wake-up only supports suspend sleep mode, not deep mode or deep retention mode.

(4) Suspend mode turns on LED2 before sleep and turns it off after waking up, deep and deep retention mode goes to sleep when the chip is powered down and LED1 turns off automatically. (LED is just to indicate the status.)

(5) Because RC clocks are inaccurate and vary with temperature, they generally need to be calibrated regularly. The following recommendations are given:

a) 24M RC

It can be calibrated every 10s, calibrated before sleep, this accuracy will affect the start time of the crystal after sleep. Waking up from sleep, the hardware uses 24M RC clock to kick crystal, the more accurate the time, the faster the start time.

b) 32K RC

It is calibrated once after power up and wake up from deep. Because of the tricking method used in PM (using 16M to count the time of 32K fixed cycles), there is no effect on the accuracy of Timer wake-up time here.

If other modules use 32K RC, they need to be handled according to the application requirements.

c) 32K xtal

It is needed to kick crystal after power up. In addition, when using 32K xtal, you need to solder a capacitor externally.

# Chip difference

## Sleep current value

Set The CURRENT_TEST current test macro to 1, test the sleep current in uA (this is a chip test data, for reference only, you can refer to the datasheet for details).

Sleep current value of B91 A0 chip:

|  - |Pad ldo|Pad dcdc|32k rc ldo|32k rc dcdc|32k xtal ldo|32k xtal dcdc|mdec ldo|mdec dcdc|lpc ldo|lpc dcdc|
|:-------------------------:|:---:|:---:|:------:|:------:|:--------:|:--------:|:----:|:----:|:---:|:---:|
|deep|0.7|0.7|1.3|1.2|1.7|1.6|1.4|1.4|1.6|1.6|
|deep retention 32k sram|1.8|1.8|2.4|2.4|2.8|2.7|2.6|2.6|2.8|2.8|
|deep retention 64k sram|2.7|2.7|3.2|3.2|3.7|3.6|3.4|3.4|3.7|3.8|

Sleep current values for the B91 A1 chip:

| #9 |Pad ldo|Pad dcdc|32k rc ldo|32k rc dcdc|32k xtal ldo|32k xtal dcdc|mdec ldo|mdec dcdc|comp. ldo|comp. dcdc|core ldo|core dcdc|
|:------------:|:---:|:---:|:------:|:------:|:--------:|:--------:|:----:|:----:|:---:|:---:|:---:|:---:|
|suspend|36.6|36.7|37.1|37.1|36.8|37.1|37.1|36.8|37.9|37.7|37|36.8|
|deep|0.6|0.5|1.1|1.1|1.5|1.4|1.1|1.0|1.5|1.5|-|-|
|deep ret 32k|1.8|1.7|2.3|2.2|2.7|2.5|2.3|2.2|2.7|2.7|-|-|
|deep ret 64k|2.7|2.6|3.1|3.1|3.5|3.4|3.2|3.1|3.6|3.1|-|-|

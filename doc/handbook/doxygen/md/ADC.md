@page ADC_Example ADC


# Introduction

The ADC driver can be used for ADC sampling of external GPIO voltage, battery voltage and temperature sensor.

# Working principle

## Internal structure

Internal structure of SAR_ADC, as shown below:  

![Internal structure of ADC](pic/sar_adc_internal_structure.png "Internal structure of ADC")  

SAR ADC only supports differential mode. The code value is obtained through differential sampling, and then converted into voltage value or temperature value by the driver.

|Application scenario|  P end  |   N end  |
|:------------------|:----------|:------------|
| Single GPIO sampling | ADC_GPIO | GND |
| Two GPIO differential sampling | ADC_GPIO1 | ADC_GPIO2 |
| Vbat channel | VBAT | GND |
| Temp sensor | ADC_TEMSENSORP_EE | ADC_TEMSENSORN_EE |

**Requirements for P end and N end voltage:**

For the sampling range of a single GPIO, refer to (1) and (2) below to determine the final sampling range.  

The application scope of two GPIO differential sampling needs to meet the following four conditions:

(1) The voltage of P end and N end is not allowed to exceed prescal * vreference.

(2) The voltage of P end and N end is not allowed to exceed V_ioh (Voltage value at IO output high level).

(3) The difference voltage between P end and N end is not allowed to exceed prescal * vreference.

(4) ((Vp+Vn)/2)<(prescal*Vreference).

|Chip|V_ioh(Voltage value at IO output high level)|
|:-----|:-------------------------------------------------------------------------------------|
|  B85  |  V_ioh=vbat<3.6v  |
|  B87  |  V_ioh=vbat<3.6v  |
|  B91  |  (1) When the Vbat voltage in the application scenario must be lower than 3.6V, set Vbat_MAX_VALUE_LESS_THAN_3v6 mode. (2) When the Vbat voltage in the application scenario may be higher than 3.6V, set VBAT_MAX_VALUE_GREATER_THAN_3V6 mode, V_ioh follows vbat when vbat < V_ldo, and V_ioh = V_ldo when vbat > V_ldo. (V_ldo=3.3v(+-10%))|

## Sampling voltage value calculation

The analog input voltage ($V_{IN}$) is compared with the reference voltage ($V_{REF}$) to generate a proportional N-bit sample code value, which is stored in a register. In actual application we will generally do pre-scale to $V_{IN}$ to support a larger sampling range. Taking the 14-bit resolution sampling code value as an example, when the pre-scale factor pre_scale = ¼, the conversion formula between $V_{IN}$ and code value is:

$$\frac {{\frac 14}*{V_{IN}}}{V_{REF}} = \frac {adc\_code}{ref\_code}$$

Among them, adc_code is the code value obtained by sampling $V_{IN}$ .

The ref_code is the code value converted from $V_{REF}$ , 14-bit resolution corresponds to 0x1fff (bit13 is the sign bit).

The inverse of this can be used to obtain the sampled voltage value of $V_{IN}$.

**Note:**

> - For GPIO, after pre-scale it can be compared with the reference voltage as a differential signal. However, Vbat can be compared only after two voltage dividers of Vbat divider and pre-scale. The final voltage divider factor is the product of two voltage divider factors. e.g. when the pre-scale factor pre_scale = 1 and Vbat_divider = 1/3, the conversion formula between $V_{IN}$ and code value is:  

$$\frac {{\frac 13}*{1}*{V_{IN}}}{V_{REF}} = \frac {adc\_code}{ref\_code}$$

# B91 ADC instructions

## Interface description

The interface naming rule is:

- init suffix: the interface used for initialization.
- dma suffix: the interface that will be used for dma mode sampling.
- No dma suffix: the interface that will be used for manual sampling.

# Demo description

## Demo structure description

The application.c file for ADC Demo is app.c, and the macro ADC_MODE in ADC_Demo/app_config.h selects which sampling mode to use.

```C
#define ADC_DMA_MODE				 1
#define ADC_NDMA_MODE				 2

#define ADC_MODE 			   ADC_NDMA_MODE
```

In ADC_NDMA_MODE (manual sampling mode) and ADC_DMA_MODE (DMA sampling mode), the ADC usage scenario is selected by configuring the macro ADC_SAMPLE_MODE for one of GPIO analog signal input, battery voltage (Vbat) and temperature sensor.

```C
#define ADC_GPIO_SAMPLE			 1	//GPIO voltage
#define ADC_VBAT_SAMPLE			 2	//Vbat channel Battery Voltage
#define ADC_TEMP_SENSOR_SAMPLE	         3      //Temp test
#define ADC_SAMPLE_MODE		   ADC_GPIO_SAMPLE
```

## ADC initialization configuration

The ADC initialization flow is shown in the following figure:

![ADC initialization flow](pic/adcinitializationflow.png "ADC initialization flow")

## ADC sampling and conversion process

The sampling and conversion of the ADC is shown in the following figure:

![ADC sampling and conversion](pic/adcsamplingandconversion.png "ADC sampling and conversion")

**Note:**

> - When sampling (ADC_NDMA_MODE) manually, only one adc_code can be acquired at a time, during which the ADC sampling function will be turned off, and when using, it is necessary to ensure that the time interval between continuous acquisition of adc_code is greater than 2 sampling cycles.

## Demo test example

Sample Vbat using the method of configuring DMA.

The sampling results are viewed through the BDT tool as follows:

![Sampling results](pic/samplingresult.png "Sampling results")

In the above figure: adc_sample_buffer stores the code values of 8 sets of samples, adc_vol_mv_val represents the sampled voltage value, 0xae2 converted to decimal is 2786mV (2790mV measured by voltmeter).

# Chip difference

## Feature support differences

|Chip|GPIO sampling|Vbat sampling mode|Whether Temp sampling is supported|
|:---|:-----------|:------------------------------------------|:-------------------|
|B85|PB0-7/PC4-5|Vbat channel mode is not supported, using GPIO output high level, to GPIO sampling way of vbat sampling, at this time the GPIO voltage is the voltage of Vbat. (This method does not require hardware wiring, you can set a pin without package to save GPIO resources.)|not support|
|B87|PB0-7/PC4-5|vbat channel|support|
|B91|PB0-7/PD0-1|The external voltage divider is used in the hardware circuit, and the GPIO method is used for sampling in the software|support|

## Calibration configuration description

The configurations with chip level calibration are listed below. It is recommended to use these configurations to reduce the error (if other configurations are used, the calibration value is inaccurate). If you want the error to be smaller, you can use a fixture for board level calibration on the production line.

|Chip|Factory calibration value|Sampling error (The amount of test data is small and is only for reference)|
|:---|:-------------------------------------------------------------|:-------------------------------|
|B85|GPIO sampling, sampling rate 96KHz, pre-scale factor 1/8, reference voltage 1.2V.|Error in -14~12mV. (29 sample chips)|
|B87|GPIO sampling, sampling rate 96KHz, pre-scale factor 1/8, reference voltage 1.2V.|Error in 9~12mV. (20 sample chips)|
|B87|vbat channel sampling, sampling rate 96KHz, pre-scale factor 1, vbat scale factor 1/3, reference voltage1.2V.|Error within 10mV. (10 sample chips)|
|B91|GPIO sampling, sampling rate 48KHz, pre-scale factor 1/4, reference voltage 1.2V.|Error in -11~7mV. (19 sample chips)|

**Distinction between signal-to-noise ratio and error concepts**

The datasheet of B91 indicates that the signal-to-noise ratio is 10.5bit, which means as follows:

The signal-to-noise ratio (significant bit) is 10.5 bits, and the corresponding analog quantity is 1200mV/（2^10.5）≈0.82mV (assuming reference voltage selection 1200mV), which means that the sampling accuracy of ADC is 0.82mV, that is, the code value of 1 unit represents the voltage value of 0.82mV.

The concept of error, e.g. the error is 10mV, the input is 500mV, and the sampling result is 510mV.

**External voltage divider circuit**

When the voltage to be sampled exceeds the ADC sampling range, an external voltage divider circuit must be used to divide the original voltage to the sampling range, and then input to the sampling point for sampling through GPIO. The recommended configuration of the external voltage divider circuit is as follows (it can be selected according to the respective application requirements):

Hardware circuit reference:

As the chip internal resistance is tens of Mbps, so the total resistance values of the voltage divider circuit should not be too large (preferably not more than 2M), otherwise the current is too small and the ADC cannot sample normally.

***M-level voltage divider circuit: small leakage, slow sampling***

![M-level voltage divider circuit](pic/schematicdiagramofMlevelvoltagedividercircuit.png "M-level voltage divider circuit")

***Hundred K-level voltage divider circuit: large leakage, fast sampling***

![Hundred K-level voltage divider circuit](pic/schematicdiagramof100Klevelvoltagedividercircuit.png "Hundred K-level voltage divider circuit")

Software requirements:

The input equivalent of sar adc is a capacitance of about 15pF, and there will be a dynamic current equivalent to $f*c*v$ in the sampling, so the voltage value of the sampling point of the resistor divider will slowly produce an error voltage. So

(1) When the ADC is turned on to sample immediately, the value of the sampling point is still in a more accurate place, so the sampling value is more accurate.

(2) Delay after closing ADC, the resistance value at the voltage divider point will return to the accurate value due to no dynamic current.

(3) The higher the sampling rate, the greater the error voltage.

***There are different solutions for different working modes. Take B91 as an example to illustrate.***

***(The delay part marked below will be related to the sampling frequency, voltage and current, so when using only need to refer to the following logic processing method, but the relevant delay part, please test according to the actual application, and set aside a certain amount of margin out.)***

Hardware configuration: B91 calibration chip + M-level voltage divider circuit

Software configuration (ADC_Demo):

- 1.2V Vref reference voltage
- 1 / 4 pre_scale pre-voltage-dividing factor
- Sampling frequency 23K

(1) In normal operating mode:  
        a. Turn on the ADC to sample immediately, and then turn off the ADC immediately.  
        b. Delay (greater than 50ms, less than this value error will be larger).  
        c. Perform the next sampling, the sampling steps are the same as a and b.

**Note:**

> - If you need to switch the PIN, the operation of switching the PIN can be added before step a.

(2) In the deep or deep retention mode, after sampling, it will enter the deep or deep retention  without additional operation.

(3) In the suppend mode, it will enter the suppend after sampling, and the time to configure suppend is greater than 200ms.

Chip level calibration error is - 9 \~ 5mV; The board level calibration error is - 3 \~ 8mV. (10 sample chips)

Hardware configuration: B91 calibration chip + Hundred K-level voltage divider circuit

Software configuration (ADC_Demo):

- 1.2V Vref reference voltage
- 1 / 4 pre_scale pre-voltage-dividing factor
- Sampling frequency 23K

(1) In normal operating mode:  
        a. Turn on the ADC to sample immediately, and then turn off the ADC immediately.  
        b. Delay (greater than 5ms, less than this value error will be larger).  
        c. Perform the next sampling, the sampling steps are the same as a and b.

**Note:**

> - If you need to switch the PIN, the operation of switching the PIN can be added before step a.

(2) In the deep or deep retention mode, after sampling, it will enter the deep or deep retention  without additional operation.

(3) In the suppend mode, it will enter the suppend after sampling, and the time to configure suppend is greater than 50ms.

Chip level calibration error is - 5 \~ 7mV; The board level calibration error is - 4 \~ 6mV. (10 sample chips)

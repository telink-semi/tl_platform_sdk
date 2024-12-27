@page LPC_Example LPC

# Introduction

The Low Power Comparator (LPC for short) compares the input voltage multiplied by the selected scale factor with a reference voltage and outputs the result of the comparison. There are two working modes of the LPC, which are:

(1) Normal mode, the internal reference voltage is from bandgap (BG for short), it has higher accuracy, high power consumption, and works in the chip's normal power supply environment.

(2) Low power mode, internal reference voltage is from UVLO, it has lower accuracy, low power consumption, and works in the chip sleep environment.

The output of the low-power comparator can also be used as a signal to wake up the system from low-power mode.

# Working principle

The LPC requires a 32K RC clock source to be used as the comparator clock. The comparison results are as follows:

(1) If the value of [Input Voltage * Scaling] is greater than the reference voltage, the output will be low ("0").

(2) If the value of [Input Voltage * Scaling] is less than the reference voltage, the output will be high (" 1").

(3) If the value of [Input Voltage * Scaling] is equal to the reference voltage, or if the input channel is selected as float, the output will be indeterminate.

# Demo description

Demo flow chart is as follows:

![Demo flow chart](pic/demoflowchart1.png "Demo flow chart")

The reference voltage value is set to 872mv, and the scaling ratio is set to 50%, then when the input voltage is 0 \~ 1.744V, the lpc_get_result returns "1"; and when the input voltage is 1.744 \~ 3.3V, the lpc_get_result returns "0".

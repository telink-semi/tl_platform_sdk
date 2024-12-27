@page Coremark_Example Coremark

One important measure of a processor is power consumption, and another important measure is performance. There are many benchmarks in the processor area, the most well-known and common benchmarks in the embedded processor area are Dhrystone and CoreMark.

# Dhrystone

The Dhrystone standard test method is simple, it is how many times the Dhrystone program is run per unit time, and its metric unit is DMIPS/MHz. The MIPS stands for Million Instructions Per Second, the number of million machine language instructions processed per second. The D in DMIPS is an abbreviation for Dhrystone, which indicates the MIPS under the Dhrystone standard test method, mainly used to measure integer computing power.

# CoreMark

The CoreMark program is written in C and contains the following four types of algorithms: mathematical matrix operations (normal matrix operations), enumeration (find and sort), state machine (used to determine whether the input stream contains valid numbers), and CRC (cyclic redundancy check). Similar to Dhrystone, the standard CoreMark test method is how many times the CoreMark program is run per unit of time under a certain combination of configuration parameters, with the metric unit of CoreMark/MHz. The higher CoreMark numbers mean the higher performance.

# Testing

Dhrystone_Demo and CoreMark_Demo are for Dhrystone and CoreMark tests, respectively, with the test information exported from the USB.

---------------------------------
Benchmarks  Test results  Remarks
----------  ------------  -------
Dhrystone   2.7 (DMIPS)   attach1

CoreMark    3.38          attach2
---------------------------------

**Note:**

> - To improve the test performance, the link file corresponding to the two demos is flash_boot_ramcode.link.

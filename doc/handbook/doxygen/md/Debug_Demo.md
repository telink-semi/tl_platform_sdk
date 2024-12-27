@page Debug_Example Debug

The driver does not redefine the printf interface, it directly uses the printf interface that comes with toolchain. However, we redirect it, the driver implements two kinds of redirection, one is to redirect the data to GPIO (through GPIO to simulate serial timing), the other one is to redirect to USB. You can choose either one for debug info output.

You can choose whether to use GPIO or USB printing in printf.h.

```C
#define DEBUG_IO         0
#define DEBUG_USB        1
#define DEBUG_BUS        DEBUG_IO
```

# Simulate serial output via GPIO port

GPIO port related configuration is configured in printf.h, including baud rate, and others (only RX and GND need to be connected). The hardware connections are as follows:

![The hardware connection of GPIO port](pic/thehardwareconnectionofgpiopart.png "The hardware connection of GPIO port")

The following figure shows the printout received by the serial assistant tool:

![Printout received by the serial assistant tool](pic/printoutreceivedbytheserialassistanttool.png "Printout received by the serial assistant tool")

# USB printout

Configuring USB printf, you need to use the BDT tool to view the output information. The point to note when using USB printf is that the USB uses a fixed 48M clock, in the clock initialization it is configured by default. However, if the PLL clock used cannot be divided to get 48M, then the USB may not work properly.

When using USB printf, you can configure blocking and non-blocking modes, which can be selected through the relevant macro definitions in printf. The default is non-blocking as follows:

```C
#define BLOCK_MODE         0
```

The following is the BDT configuring usb_log method and experimental phenomena:

![BDT configuring usb_log method](pic/bdtconfiguringusblogmethod.png "BDT configuring usb_log method")

![Experimental phenomena](pic/experimentalphenomena.png "Experimental phenomena")

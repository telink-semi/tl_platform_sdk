@page GPIO_Example GPIO

The SoC's GPIO driver implements the configuration of GPIO inputs and outputs, pull-ups and pull-downs, interrupts, and other functions.

# Interrupt

GPIO can be configured to generate interrupts. The interrupt hardware structure is shown in the figure below. Each GPIO can be configured to generate three types of interrupts, GPIO_IRQ, GPIO2RISC0_IRQ, and GPIO2RISC1_IRQ. GPIO_IRQ is the most basic GPIO interrupt, GPIO2RISC0_IRQ and GPIO2RISC1_IRQ can generate count or control signals in Timer (timer peripheral) applications, in addition to the GPIO_IRQ functions.

![Interrupt hardware architecture](pic/interrupthardwarearchitecture.png "Interrupt hardware architecture")

## Mechanism description

As shown in the figure below, the GPIO is set to trigger at rising edge. The mechanism of MCU is that the level signal of GPIO is used as the signal to generate interrupt and trigger the interrupt at rising edge.

![GPIO set to trigger at rising edge](pic/gpiosettotriggeratrisingedge.png "GPIO set to trigger at rising edge")

As shown in the figure below, the GPIO is set to trigger at falling edge. The mechanism of MCU is to invert the level signal of GPIO and then use the inverted signal as the signal for interrupt generation, and trigger the interrupt at rising edge.

![GPIO set to falling edge trigger](pic/gpiosettofallingedgetrigger.png "GPIO set to falling edge trigger")

As shown in the figure below, if two GPIOs are set as one kind of interrupt, trigger at rising edge, the mechanism of MCU is that the level signal of two GPIOs will be or operation, and then use the obtained signal as the condition to generate interrupt, trigger the interrupt at rising edge. In this figure, only GPIO0 triggers the interrupt.

![Two GPIOs set to one interrupt, trigger at rising edge](pic/twogpiossettooneinterrupttriggeratrisingedge.png "Two GPIOs set to one interrupt, trigger at rising edge")

As shown in the figure below, if two GPIOs are set as one kind of interrupt, trigger at falling edge, the mechanism of MCU is to invert the level signals of two GPIOs respectively, and then make or operation for the inverted signal, and use the obtained signal as the condition to generate interrupt, which also triggers interrupt at rising edge. That is, finally MCU uses the final signal to trigger the interrupt at rising edge. In the figure, only GPIO0 triggers the interrupt.

![Two GPIOs set to one interrupt, trigger at falling edge](pic/twogpiossettooneinterrupttriggeratfallingedge.png "Two GPIOs set to one interrupt, trigger at falling edge")

As shown in the figure below, if GPIO0 is set to trigger at rising edge and GPIO1 is set to trigger at falling edge, the mechanism of MCU is to invert the level signal of GPIO1, then make or operation for GPIO0 and (!GPIO1), and use the obtained signal as the condition to generate interrupt, which also trigger interrupt at rising edge. That is, finally MCU is using the final signal to trigger the interrupt at rising edge. In the figure, only GPIO1 triggers the interrupt.

![GPIO0 set trigger at rising edge, GPIO1 set trigger at falling edge](pic/gpio0settriggeratrisingedgegpio1settriggeratfallingedge.png "GPIO0 set trigger at rising edge, GPIO1 set trigger at falling edge")

## Conclusion

Two or more GPIOs set as one kind of interrupt, depending on the timing of input GPIO, triggering interrupts is uncertain and not recommended. However, the mechanisms of different GPIO interrupts are independent of each other. If one GPIO is set to one kind of interrupt, the interrupts of both GPIOs can be triggered.

For example, GPIO0 is set to GPIO_IRQ interrupt and GPIO1 is set to GPIO_IRQ_RSIC0 interrupt, both configured to be triggered at rising edge. In the figure below, signals 0 and 1 are the input timing of GPIO0 and the toggle signal set within the interrupt handler function to observe the GPIO0 interrupt, and signals 2 and 3 are the input timing of GPIO1 and the toggle signal set within the interrupt handler function to observe the GPIO1 interrupt, respectively. In this figure, both GPIO1 and GPIO2 trigger the interrupt.

![Two or more GPIOs set different interrupts](pic/twoormoregpiossetdifferentinterrupts.png "Two or more GPIOs set different interrupts")

**Note:**

> - Since there are only three GPIO interrupts, GPIO_IRQ, GPIO_IRQ_RSIC0, and GPIO_IRQ_RSIC1, up to three GPIO interrupts can be set at the same time.

# Attentions

If setting the trigger type as high or trigger at rising edge, pull-down resistor should be set; if setting the trigger type as low or trigger at falling edge, pull-up resistor should be set.

Two other issues that do not require concern to the application layer are also briefly explained here (they are addressed in the driver interface).

When setting trigger at falling edge, you need to clear the interrupt bit after setting the polarity of GPIO, and then enable mask. (Otherwise, when setting GPIO to trigger at falling edge, a non-falling edge caused interrupt trigger is generated at the moment of enabling GPIO interrupt.) This part has been handled in the corresponding interrupt enable function of GPIO, and does not require the application layer to care.

GPIO multiplexing function switching notes:

(1) It starts with GPIO function, so you need to configure the required function MUX first, and then disable the GPIO function at the end.

(2) It starts with IO function, and needs to change to GPIO output. First set the corresponding IO output value and OEN set correctly, and enable GPIO function at the end.

(3) It starts with IO function, and needs to be changed to GPIO input.

Need pull up this IO:

Case 1 (digital pull-up): set output to 1 and OEN to 1;

Case 2 (analog pull-up): set pullup to 1.

No need to pull up:

Case 1 (digital pull-up): set output to 0 and OEN to 1;

Case 2 (analog pull-up): set pullup to 0.

Finally enable the GPIO function.

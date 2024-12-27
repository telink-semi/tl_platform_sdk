@page MDEC_Example MDEC


MDEC is the Manchester Decoding Module.

# Test environment setup

The working environment for implementing the MDEC function consists of two other boards in addition to the development board:

(1) AT9001H-V1.1: Receive RF data and send the data out through MCU_1.

(2) E21480094v-0: Send RF data to the AT9001H-V1.1 board.

In the figure of AT9001H-V1.1, the black cable is GND, the red cable is MCU_1, the long iron piece on the right is GND, and the diagonal iron above is VBAT. When wiring, please note that MCU_1 should be connected to the MDEC function pins (PA0 on the silkscreen) set in the development board. The red cable of PCB board E21480094v-0 is 24V+ and the black cable is 24V-.

![PCB board AT9001H-V1.1](pic/pcbboardat9001hv11.png "PCB board AT9001H-V1.1")

![PCB board E21480094v-0](pic/pcbboarde21480094v0.png "PCB board E21480094v-0")

In addition, the PCB board E21480094v-0 requires a 24V regulated voltage source to supply power. The specific wiring schematic is as follows:

![Wiring diagram](pic/wiringdiagram.png "Wiring diagram")

![Wiring diagram](pic/wiringdiagram1.png "Wiring diagram")

When the environment is set up and powered on, the board E21480094v-0 will continuously send wireless packet data content, when the board AT9001H-V1.1 receives the data it will send through MCU_1 to the SoC's Manchester interface IO in the form of levels. Pay attention to place the two boards as close as possible, and the correct level waveform is as follows:

![Level waveform](pic/levelwaveform.png "Level waveform")

**Note:**

> - If you see a messy waveform, reposition the two boards and adjust the long black coil in the connector at the bottom of the E21480094v-0.

# Function description

Using the MDEC module requires a 32K clock to be turned on, where both 32K RC and 32K Xtal are suitable. The relevant data is obtained and determined by reading the voltage level of the Manchester input pin. It can be used for MDEC wake-up in low-power mode.

**Note:**

> - The 32K clock source is used because the MDEC is designed to be used as a wake-up source in deep and suspend scenarios.

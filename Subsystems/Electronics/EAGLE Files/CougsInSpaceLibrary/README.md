# Cougs in Space EAGLE Libraries #
These are the footprints used in Cougs in Space. These libraries are based off of the [Sparkfun Libraries](https://github.com/sparkfun/SparkFun-Eagle-Libraries).
- [Library Descriptions](#library-descriptions)
- [Library Guidelines](#library-guidelines)
  - [Symbols](#symbols)
  - [Packages](#packages)
  - [Devices](#devices)
    - [Reference Designators](#reference-designators)

## Library Descriptions
- **Aesthetics** - Non-functional items such as logos, build/ordering notes, frame blocks, etc.
- **Boards** - Standard boards, non-RF modules, etc.
- **Capacitors** - Various capacitor types, sizes, and values.
- **Clocks** - Real-time clocks, oscillators, resonators, and crystals.
- **Coils** - Inductors, ferrites, transformers, etc.
- **Connectors** - Various PTH and SMD connectors. Also has test points.
- **DiscreteSemi** - Diodes, optoisolators, thyristors, MOSFETs, transistors, etc. excluding LEDs
- **Energy** - Energy sources, i.e. solar cells, batteries
- **Fuses** - Resettable fuses, i.e. PTCs.
- **Hardware** - Stand offs, heatsinks, etc.
- **IC-Amplifiers** - Mostly operational amplifiers but also has some headphone and audio amps with more specific applications
- **IC-Comms** - USB to serial conversion ICs, like the FTDI line, plus high speed line drivers, level shifters, bus drivers, CAN transceivers and ethernet PHYs.
- **IC-Conversion** - Analog to digital conversion, as well as digital to analog. This includes not only strict ADCs, but audio in and out converters, decoders, thermocouple measurement ics the like. Anything that is a single part that works between the two domains goes here.
- **IC-Logic** - Standard logic IC families.
- **IC-Memory** - Volatile and non-volatile memory. i.e FLASH, EEPROM, RAM
- **IC-Other** - 555 timers, LED drivers, Motor Control, etc. ICs that do not really fit into the other, more generic categories. Basically, anything that serves some function but has a bunch of brains or special bias circuitry that prevents it from being used as a general part qualifies for this category.
- **IC-Power** - Anything that has to do with power delivery, or making power supplies.
- **IC-µController** - Various microcontrollers, and CLPD, FPGA, etc. Essentially any programmable IC.
- **LED** - Illumination or indication
- **PowerSymbols** - Power, ground, and voltage-supply symbols.
- **Resistors** - Various resistor types, sizes, and values.
- **RF** - Devices that send or receive RF
- **Retired** - All manner of retired footprints for resistors, capacitors, board names, ICs, etc., that are no longer used in our catalog.
- **Sensors** - Accelerometers, gyros, compasses, magnetometers, light sensors, imagers, temp sensors, etc.
- **Switches** - Switches, buttons, and anything that moves to create or disrupt an electrical connection.

## Library Guidelines
These are the guidelines that every part added to the libary must follow (or try to)

### Symbols
- All symbols need `>Name` (on the **Names** layer). **Size: 0.07 Ratio: 8% Font: Vector Align: Center** located above the symbol.
- All symbols need `>Value` (on the **Values** layer). **Size: 0.07 Ratio: 8% Font: Vector Align: Center** locate below the symbol.
- Most symbols need `>SKU` (on the **Info** layer). **Size: 0.07 Ratio: 8% Font: Vector Align: Center** locate below the symbol.
- Add attributes as logical (on the **Info** layer), i.e. capacity, voltage, temperature coefficient locate below the symbol.
- Small symbols (i.e. passives) can use size 0.05 text
- Symbol Names
	- Should be the most basic name which can describe the component - reserve part numbers for technologies under the device (if applicable).
- Pins
	- Group pins **logically by function**, or place them **in the order** they appear on the physical package.
	- Aim to use **SHORT pins** if possible (bump to MEDIUM if necessary).
	- Names should follow datasheet conventions set by the manufacturer.
	- Use an exclamation point to indicate **active low** signals- e.g., `!RESET` will produce a pin name with a bar over it. `!R!/W` will place a bar over the 'R' only.
	- Don't be afraid to use **gates** to divide large pin count packages into smaller groups when necessary.
	- Be sure to match a pins direction properly
		- `nc` - Not connected
		- `in` - Input
		- `out` - Output (totem-pole)
		- `io` - Input / output (bidirectional)
		- `oc` - Open collector or open drain
		- `hiz` - High impedance (i.e 3-state)
		- `pas` - Passive (for resistors, capacitors, etc.)
		- `pwr` - Power input pin(Vcc, gnd, Vss, Vdd, etc.)
		- `sup` - Supply (reserve for supply symbols)
- Symbol Origin:
	- Headers:
		- Centered (above/below)
		- Pin 1 at top, pins to the right
		- Cross-hairs should be centered on box
- Symbol Outline
	- Default to 0.01 for outline width
- Description
	- Use the following format:

```html
<h3>[Manufacturer (if applicable)] [General Part Number (if applicable)] [Short Part Description (required)]</h3>
<p>[Few-sentence description of part(s)</p>
Example: SparkFun-DigitalIC - ATMEGA32U4
<h3>Atmel ATmega32U4 - 8-Bit Microcontroller w/ USB 2.0</h3>
<p>The low-power Atmel 8-bit AVR RISC-based microcontroller featuring 32KB self-programming flash 
program memory, 2.5KB SRAM, 1KB EEPROM, USB 2.0 full-speed/low speed device, 12-channel 10-bit A/D-converter, 
and JTAG interface for on-chip-debug. The device achieves up to 16 MIPS throughput at 16 MHz. 2.7 - 5.5 Volt operation. </p>
```

### Packages
- Name/Value
	- All footprints need `>Name` (on the **tNames** layer). Size should be **0.8 mm, 15% ratio, vector, align center**.
	- No footprint should have `>Value`.
	- Place it above the package, the location will change during the `smash` process (final PCB layout).

- Part Outline
	- All footprints need **tDocu** outline showing mechanical size or special features, i.e. SD card insertion levels or tantalum capacitor anode nub. Often omit the leads in packages like SOIC. This layer is not silkscreened.
  - All footprints need **tPlace** (silkscreen) that reflect the following features
    - Transfer the **tDocu** dimensions without overlapping a pad.
    - Outline the **courtyard excess** of a part, *see below*.
    - Mark pin one or polarity with an appropriate symbol, often a triangle
	- Silkscreen within a footprint or board should NOT go over pads or metal that will be exposed.
	- Silkscreen of footprint should have a **width of 0.15 mm**. Make it look good.
	- No silkscreen under part - this may affect reflow negatively.

INSERT IMAGE
_Here are several footprints in use. Notice that the specifics of each part change from package to package, but the style stays consistent. Silk widths, polarity markings, paste reduction, and QFN pad windowing is illustrated._

- IPC defines standards for **courtyard excess** for component footprints.
  - These are drawn as rectangles (0.15 mm wide lines) on the **tKeepout**, or possibly **bKeepout** layers. Odd shapes are okay, i.e. magnetorquer form.
	- The courtyard is defined as the smallest rectangular area that can contain the component and its land pattern.
	- Courtyard excess is a buffer around this to mark the minimum electrical and mechanical clearances around the courtyard.
	- Use 0.25 mm courtyard excess rounded to the nearest 0.05 mm. This is nominal defined by the standard. 

INSERT IMAGE
_Example of 0.2 mm courtyard excess for an 1608 package_

- Pins
	- Make pin names numeric.
		- BGA pins should be labeled by their standard alphanumeric code.
	- Components with exposed pads on the underside should use "EPAD" for that pin.
	- Include a **polarity/pin 1 marking** on the **tPlace** (silkscreen).
		- Ensure this marking is visible after the component is placed on board.
		- Draw a triangle, cathode stripe, or fill in the courtyard excess area on the cathode side.
- Before you make a new footprint, check the existing Cougs in Space libraries to see if it exists.
- If possible, compare a 1:1 printout with a sample of the part you created before you order prototypes.
- Be sure that pads have the "Thermals" box checked- this ensures thermal relief traces will connect the pad to planes, make it easier to solder.
- **Footprint origin** set as follows:
	- Headers: Pin 1 position: 0,0 in the center of the drill hit. Additional pins grow to the right. (Y: 0) (X: 0.1, 0.2, 0.3 etc)
	- Everything: Center of device, or the most logical location
- Every new footprint and part will have a **description** containing part information and whether the footprint has been proven.
    - Use the following format: 

```html
<h3>[Package Name] - [Package Short Description]</h3>
<p>Specifications:
<ul><li>Pin count: [PIN COUNT]</li>
<li>Pin pitch: [PIN PITCH]</li>
<li>Area: [WIDTH x LENGTH]</li>
</ul></p>
<p><a href=””>Datasheet referenced for footprint</a></p>
<p>Example device(s):
<ul><li>[EXAMPLE DEVICE 1]</li>
<li>[EXAMPLE DEVICE 2]</li>
</ul></p>
```

### Devices
- When creating a device, give it a name which indicates the **manufacturer's part number**. 
	- If multiple part numbers can share the same device (eg, 32-pin QFP and 32-pin DFN versions of the same device), give the device a good generic name (ATMEGA328P_32PIN).
- Device Prefixes must use one of the approved International standard reference designators.
        - See [Reference Designators](#reference-designators) for a list!
	- If a part automatically puts a **"$" in the name**, it needs to be fixed. Open the library, click on the "device." Select the problem device. Click on "Prefix" button. Type the correct prefix letter. Save and update the library.
- Split devices into **gates** when appropriate (e.g., 7400 logic chips, op-amps, etc). Name the gates to avoid the $ in the gate name. Set swap flag if valid.
- Use **Attributes** to record the following pieces of information about the device:
	- `PROD_ID` - **Production part number** (if applicable; otherwise, assign this value NA),
	- `VALUE` - The **value** of the part (1k, 0.1uF, etc).
- Description
	- Device descriptions should include:
		- A brief description ("12-bit one-channel SPI/I2C ADC"). This should be on the first line, so it shows up when one is browsing the library.
		- Manufacturer's name (for single-source parts).
		- More information about the device (voltage range, for instance).
	- Use the following format:

```html
<h3>[Manufacturer (if applicable)] [General Part Number (if applicable)] - [Short Part Description (required)]</h3>
<p>[Few-sentence description of part(s)]</p>
<p><b>SparkFun Products:</b>
<ul><li><a href=”[DATASHEETLINK to Resources Github Repository]”>[Variant 1]</a></li>
<li><a href=”[DATASHEETLINK]”>[Variant 2]</a></li>
<li><a href=”[DATASHEETLINK]”>[Variant 3]</a></li>
</ul></p>
```

#### Reference Designators
International Standard Reference Designators (and some others we've agreed upon):

<table>
<tr><th>Designator</th><th>Acceptable Parts</th></tr>
<tr><td>B</td><td>Board, Module</td></tr>
<tr><td>BT</td><td>Battery</td></tr>
<tr><td>C</td><td>Capacitor</td></tr>
<tr><td>CN</td><td>Capacitor Network</td></tr>
<tr><td>D</td><td>Bridge Rectifier, Diode, Zener</td></tr>
<tr><td>DS</td><td>Signaling Dode (LED)</td></tr>
<tr> <td>F</td><td>Fuse, Resettable Fuse</td></tr>
<tr> <td>FB</td><td>Ferrite Bead</td></tr>
<tr><td>FD</td><td>Fiducial</td></tr>
<tr><td>FL</td><td>Filter</td></tr>
<tr><td>H</td><td>Hardware</td></tr>
<tr><td>J</td><td>Jack, Connector, Combination of Connectors, Row of Headers, Plug</td></tr>
<tr><td>JP</td><td>Jumper</td></tr>
<tr><td>K</td><td>Relay</td></tr>
<tr><td>L</td><td>Inductor (_not_ including ferrite bead), Coil</td></tr>
<tr><td>LOGO</td><td>Artwork, Logo</td></tr>
<tr><td>LS</td><td>Loudspeaker, Buzzer</td></tr>
<tr><td>M</td><td>Motor</td></tr>
<tr><td>MK</td><td>Microphone</td></tr>
<tr><td>Q</td><td>Transistor (all types)</td></tr>
<tr><td>R</td><td>Resistor</td></tr>
<tr><td>RN</td><td>Resistor Network</td></tr>
<tr> <td>RT</td><td>Thermistor</td></tr>
<tr><td>RV</td><td>Varistor</td></tr>
<tr><td>S</td><td>Switch, Push Button</td></tr>
<tr><td>T</td><td>Transformers</td></tr>
<tr> <td>TC</td><td>Thermocouple</td></tr>
<tr><td>TP</td><td>Test Point</td></tr>
<tr> <td>U</td><td>IC, Inseparable Assembly</td></tr>
<tr><td>V</td><td>Vacuum Tube, Tube</td></tr>
<tr><td>VR</td><td>Variable Resistor (potentiometer)</td></tr>
<tr><td>Y</td><td>Resonator, Oscillator, Clock Generator</td></tr>
</table>

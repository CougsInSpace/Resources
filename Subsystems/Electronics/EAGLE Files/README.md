# Cougs in Space EAGLE Guidelines #
These are the guidelines that every schematic and board created must follow (unless there is a good reason)
- [Schematics](#schematics)
- [PCBs](#pcbs)

## Schematics
- The follow global attributes shall be set (Edit>Global Attributes>New:
	- DESIGNER: Your name
	- PART_NUMBER: CIS boards have the SKU 68-xxxx. The x's start at 1 and are incremented every new board.
	- PROJECT: [Satellite name]: [Board name] (i.e. CougSat-1: EPS)
	- REV: Schematic revision number [Major].[Minor].[Patch]. Start at 1.0.0 and increment the major every schematic redesign, increment the minor every schematic iteration (usually a *minor* change to an existing schematic) and increment the patch every github pull request.
- Every schematic shall use a frame, size A (letter) placed at the origin.
	- Add the attribute TITLE to the frame (right click>attribute>new). This is the sheet's title (i.e. Block Diagram).
	![Title Block](https://github.com/CougsInSpace/Resources/blob/master/Subsystems/Electronics/EAGLE%20Files/Images/TitleBlock.png)
	_When attributes are properly set, they will appear in the title block_
- Sheet 1: **Block Diagram**
	- Create a functional block diagram explaining the schematic to follow.
		- Use `symbols` layer with **Size: 0.15, Ratio: 8%, Font: Proportional, Align: center** text for blocks and **Width: 0.01** for blocks' outlines.
		- Use `info` layer with **Size: 0.07, Ratio: 8%, Font: Proportional, Align: bottom-right** text for page reference in the block. Place the text origin **0.05** away from the bottom right corner.
		- Use `info` layer with **Width: 0.01** for connecting arrows and **Size: 0.07, Ratio: 8%, Font: Proportional, Align: center** text for arrows' labels.
	![Block Diagram](https://github.com/CougsInSpace/Resources/blob/master/Subsystems/Electronics/EAGLE%20Files/Images/BlockDiagram.png)
	_This is a block diagram for a Cougs in Space Electrical Power Subsystem mainboard_
	- Add page numbers to blocks that correspond to their location in the document.
	- Create a table of contents in the area to the left of the title block. Use `info` layer with **Size: 0.07, Ratio: 8%, Font: Proportional, Align: top-left** text. 
- Sheets 2 and on: **Circuits Galore**
	- Logically arrange the sheets, they can be reordered but update the page numbers
- Name every net descriptively. There should be no default names "N$". This makes layout easier as you can tell what type of signal it is and how to route it
- A label does not need to be placed on a net if it is continous. A net that breaks, either between sections or sheets, needs a label, appropiate off sheet connector (Aesthetics library), and locations of the other flag(s), use sheet number and coordinate (i.e. 12A4). Use `info` label with **Size: 0.05, Ratio: 8%, Font: Proportional, Align: center-right or center-left** text for the location label and add a space before and after the text to place it a consistant distance away from the connector, see below. Use `label` command with **Size: 0.07, Ratio: 8%, Font: Proportional, Align: bottom-right or bottom-left** text for net labels.
![Off Sheet Connector](https://github.com/CougsInSpace/Resources/blob/master/Subsystems/Electronics/EAGLE%20Files/Images/OffSheetConnector.png)
_Note how to location of the connecting off sheet connectors are labeled with arrows to indicate direction._
- On a generic connector, label the nets beside the connector. Connected supply symbols should be placed nearby and do not need a labeled net.
- Do not rotate a symbol unless necessary. Replace the part with the other orientation from the library or mirror the part to flip it. If rotating needs to be done, `smash` the symbol and adjust the labels to be horizontal
	![Symbol Orientation](https://github.com/CougsInSpace/Resources/blob/master/Subsystems/Electronics/EAGLE%20Files/Images/PartOrientation.png)
	_A properly oriented symbol will have its text horizontal. Mirroring a part to flip it is okay_
- Place a component's decoupling capactitors near its power pins with a `CAD Note:` informing it is a decoubling capacitor.
- Write notes on the schematic to explain circuit operations, load options, etc. Use `info` layer with **Size: 0.07, Ratio: 8%, Font: Proportional** text. Example comments:
	- Vref: 1.25V
	- 50Ω impedance
	- I2C address: B0110101x = 0x6A | R/!W
	- Limit: 1A
- Have chained devices flow left to right. Inputs on the left and outputs on the right
- If a sheet is getting too cramped, separate the circuit onto multiple sheets if possible
- Consider using a bus to connect a lot of grouped signals
- Use separate grounds to isolate sensitve circuits. Be sure to connect them (95% of the time necessary) using an appropriate jumper, (0Ω resistor or low resistance resistor, with tolerances a 0Ω resistor can be upwards of 20mΩ which may or may not matter).
- Add `CAD Note:` to inform layout specifications
- Do not change the default setting of net widths or grid size
- When exporting a schematic, just `Microsoft Print to PDF` with **Paper: Letter, Orientation: Landscape, Alignment: Center, Area: Full, Scale factor: 1, Schematic sheets: All, Border: 0, Options: Black** setttings

## PCBs
The following are guidelines as the circuit behavior will dictate specifics of layout, impedance and such.
- **Once a board is created from a schematic, ensure both documents are open when editing** `F/B Annotation has been severed!` is a error and sometimes impossible to fix without redoing the entire board.
- Stick to 2 layers unless necessary
- Place components aligned to a 0.25mm grid. Hold `Ctrl` when selecting a component to snap it to the grid.
- Keep as many (read all) SMD components on the top side (or bottom, just a single side) to make soldering easier.
- Keep components rotated horizontally or vertically. Wierd angles are wierd.
- Use the [CougsInSpace design rules](https://github.com/CougsInSpace/Resources/tree/master/Subsystems/Electronics/EAGLE%20Files/CougsInSpace.dru) to verify manufacturability. Load it in as soon as the board is created so there are no issues later. Run it often, errors usually appear as you are routing too:
	- Minimum 0.16mm trace width with 0.16mm clearance
	- Minimum 0.3mm drill
	- Minimum 0.15mm silkscreen width
	- Tented vias < 1.0mm, unless specified
- The DRC might complain at some things that it should not. You can accept the error and it will be moved and not make noise. If you do this, be prepared to explain why you approved the error at a design review
- Keep traces horizontal, vertical, or 45°. Wierd angles are wierd and the DRU checks for this.
- Use mitered corners instead of a plain right angle. Consider a round corner for high speed signals.
- Isolate analog, digital, power, and RF sections to reduce noise.
- Use polygons for large traces if appropriate.
- Understand how return currents will flow (low impedance to ground is good)
- Some components provide a suggested layout in their datasheet. Follow this if able.
- For power traces (>200mA) use a [calculator](http://circuitcalculator.com/wordpress/2006/01/31/pcb-trace-width-calculator/) to figure the required trace width. A 200mA line works for a 0.2mm trace. Use the following parameters:
	- 1 oz thickness
	- 10°C rise
	- 25°C ambient
	- Read the internal layers results for the minimum trace width
- There are a lot of guidelines for laying out specific situations. This document would be too long so research the specific situation when you get there. Topics include:
	- Microstrip transmission lines for RF
	- Via stiching
	- Decoupling capacitors
	- Kelvin connections
	- When to ground pour
	- Using multiple vias for power or signal
	- Thermal vias
	- RF shielding cans
	- Propigatation delay with meandering traces
	- And more!
- This is a [tutorial](https://learnemc.com/pcb-layout) on laying out a PCB to minimize EMI
- **Trace layout is complete**
	- No DRC errors?
	- Ensure critical layout is correct (i.e. high frequency)
	- Renumber all of the parts in a logical order (i.e. left to right, then up to down) to ease soldering. Can run ULP `cmd-renumber` to do this, might have to play with settings to get nice results.
	- `Smash` all of the components and move their name labels to be readable. Place them logically, use arrows or blocks if necessary. Make it look good.
	- Add the following markings:
		- Cougs in Space logo (Your choice, I go with text, and satellite-15)
		- Board Name, revision, and week code (i.e. EPS V2.1.3 1806). The week code is YYWK, this [site](https://whatweekisit.com/) will help.
		- Your name, usually a signature found in the Aesthetics library
	- Print it out blown up and visually check it
	- Schedule and pass a design review then generate gerber files and order it!
	

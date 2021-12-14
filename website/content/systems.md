---
title: "Systems"
description: "An overview of our ferrofluid project's journey"
draft: false
author:
  display_name: Ferrofluid Team
date: 2021-12-13
mathjax: true
---

##### Contents: <a id="Navigation"></a>

- [Tank](#tank)
- [Magnets](#magnets)
- [Controller](#controller)
- [Firmware](#firmware)
- [Animation and Software](#animation)
- [Budget](#budget)

<a id="system"></a>
Our system is comprised of mechanical, electrical, firmware, and software subsystems (click on diagram to enlarge image):

[![system_diagram](../images/system_diagram.jpg)](../images/system_diagram.jpg)

A complete image of the final system can be seen here:

Front             |  Back
:-------------------------:|:-------------------------:
![system_image_front](../images/system_front.jpg)  |  ![system_image_back](../images/system_back.jpg)

<a id="tank"></a>

## Tank {{<navarrow Navigation>}}

Our tank is comprised of two sheets of 10" by 12" glass with thickness 3/32" separated by a 1/4" acrylic rim. They are attached with epoxy.

Next, the tank was cleaned extremely thoroughly using ammonia and hot water and scrubbed with Goof Off. Without this cleaning process, the ferrofluid would stain the glass severly, leaving the glass a brown-tinted mess.

![cool_tank](../images/cool_tank.gif)

<a id="magnets"></a>

## Magnets {{<navarrow Navigation>}}

The first plan for team FerroFish was to use PCB magnets. However, upon testing the PCB magnets, we found that they were not viable for lifting and moving ferrofluid, so the decision was made to create our own electromagnets.

Electromagnets are created by wrapping wire around a ferrous core and applying a voltage to the wire, creating a current in the wire. The current induces a magnetic field and thus magnetizes the ferrous core — creating a magnet.

The equation for the strength of the field given by our electromagnets is below:

$$B = \frac{\mu_oNI}{l}$$

Where $\mu_o$ is the permittivity of free space, $N$ is the number of turns in the wire, $I$ is the current, and $l$ is the length of the solenoid.

Electromagnets are more flexible than permanent magnets because they can be easily turned on and off by adjusting voltage. As a team, we decided that electromagnets would provide the flexibility we needed.

##### Creating our Electromagnets

We decided for cost purposes that we would create our own electromagnets rather than buying premade ones. We calculated that 1000 turns would create a magnetic field strong enough to lift the ferrofluid with reasonable current.

Creating our electromagnets was three main steps:
1. 3D print spools for winding
2. Create the magnets by winding the wire
3. Soldering jumper cables onto the magnets so they can be used with controller boards

##### 3D Printing Spools

The spools were printed in two parts and then glued together. These spools were then mounted onto the wiring rig, so wire could be wound onto them. 

![spool_cad](../images/spool_cad.png)

##### Winding the Wires

On the rig for winding the magnets, there is a counter that let the winder know when 1000 turns had been reached. Our goal for the magnet grid was a 4x4 grid, or 16 total magnets. Extra spools were printed in the event we had magnets break.

##### Soldering the Magnets

Once the magnets were wound, jumper cables were soldered onto the ends of the wires. The connection between the wire and the jumper cable was then wrapped in a heat shrink wrap to prevent shorts with other wires. A finished magnet is pictured below.

![magnet](../images/magnet.jpg)

##### Using the Magnets

We 3D printed a holder for our 4x4 magnet grid. This holder went through multiple iterations as we refined our tolerances and also created a way to hold the magnets to the tank. An image of all 16 magnets as well as the CAD for the final holder is below.


![magnet_holder_iso](../images/magnet_holder_iso.png)

![magnet_holder_iso_lower](../images/magnet_holder_iso_lower.png)

![irl_magnet_holder](../images/irl_magnet_holder.png)


##### Final Take-Aways

While originally we did not think that creating our own electromagnets would be cost or time effective, by the end of our project, it was apparent that it was our best option. 

Creating the magnets required a lot of patience and communication, but ultimately, it created a better end product as we were able to successfully make a magnet grid with them and lift the ferrofluid.




<a id="controller"></a>

## Magnet Controller and Electronics {{<navarrow Navigation>}}

Our magnet controller is based off of the [Applied Procrastination Electromagnet Control Board](https://hackaday.io/project/167056-fetch-a-ferrofluid-display/log/197057-fetch-v2-massive-hardware-upgrade) schematic. The main idea is to control an LED driver via I2C from your microcontroller to turn electromagnets on or off. The current out of the driver is not large enough to power the electromagnets, however, so we placed the signal through a Darlington transistor array. We included two sets of header pins for our input signals and power rails, so we could chain together multiple boards, if we chose to expand the display.

The controller has 16 output pins, which connect to the 4 by 4 magnet array. It receives I2C messages from the Arduino Mega, which can be programmed via Serial or with an SD card with animations preloaded (click to enlarge schematics). 


[![controller_kicad](../images/controller_kicad.png)](../images/controller_kicad.png)


Pullup resistors for I2C were selected based on [Adafruit schematics](https://learn.adafruit.com/assets/36269) for our LED driver. The capacitor values were chosen with help from Course Assistants Lauren and Corey as well as the Adafruit schematic.

The Arduino Mega was used due to an unfortunate frying of our Teensy 4.1 (may it rest in peace). The Arduino Mega has more memory than an Uno but has less memory and is slower than the Teensy.

[![block_diagram](../images/block_diagram.jpg)](../images/block_diagram.jpg)



<a id="firmware"></a>

## Firmware {{<navarrow Navigation>}}

<!-- TODO: link to system diagram here? -->
As shown in our [system diagram](#system), a microcontroller plays back animations by sending commands over I2C to the PCA9685 PWM driver. This gives the firmware a few responsibilities:
 1. Read animations from the animation generator in an agreed-upon format from the SD card or serial, or read other debug commands from serial.
 2. Interpolate to create smooth fades between frames and space apart animation frames over time.
 3. Send commands to the PCA9685 over PWM. 

To do this we have a simple state machine with states of "off", "manual", "SD", and "serial". The "off" state turns off all magnets and immediately transitions to "manual"; "manual" stays in manual and waits for commands over serial; "SD" reads animation frames from the SD card until it reaches the end of the file and then transitions to off; "serial" reads animation frames from serial until the serial buffer is empty for long enough for reads to time out. This state machine design means our code is fully interruptable by user commands, and it makes it very easy to add new commands and states, which was important during prototyping because we decided to add serial streaming when we had SD card problems and to better support our presentation at EXPO.

The "serial" and "SD" states use the same parsing code; because both the SD file object (`FsFile`) and the Arduino `Serial` object inherit from the Arduino `Stream` object, we can use the same code for parsing files and for parsing serial streams, as the formats are designed to be the same. We used a text-based format for instead of a binary format to avoid endianness and struct packing issues and to make our parsing code easy to modify and read by everyone on the team.

The firmware was written in C++17 and tries to do things in a C++ style where possible. This mostly means using `constexpr` instead of preprocessor macros for constants, `if constexpr` instead of preprocessor conditionals, `std::array` instead of C-style arrays, and C++-style includes of C standard library headers. We also define our own classes for managing the hardware. Their interfaces are equivalent so we can switch between different PWM drivers (e.g. between a simple PWM driver and an interpolating PWM driver). This was useful for initial debugging before we had brought up all the hardware, which helped a lot with integration.

We've used both an Arduino Uno and Mega and Teensy 4.1 and we ultimately needed to support all three because we prototyped with the Uno and initially used the Teensy until our perfboard failed and shorted the Teensy. This led us to switch to the Arduino Mega, which has a little bit more memory than the Uno (which we needed). The GCC toolchain for the Teensy includes all of the C++ standard template library, but the Arduino toolchian (`avr-gcc`) doesn't, so we also include the `avr_stl` library and conditionally include it if we're on an AVR-based board.

The portability of the code across microcontrollers was a very important part of having a smooth integration process for us because it enabled early prototyping without setting up the Teensy, and it allowed for a plan B when we had damaged our hardware.

We don't use the Adafruit servo driver hardware (we have custom-designed PCBs), but we use the library that comes with it because it's a complete and easy-to-use implementation of all the PCA9685's I2C commands. We also use Bill Greiman's SdFat library for reading from the SD card. We chose this over the Arduino-default one because it supports SDIO if the hardware has that capability (the Teensy 4.1 can do SD over SDIO instead of just SPI.)

<a id="animation"></a>

## Animation Generator

The user needs to be able to easily draw animations. The microcontroller needs to have animations in a format it can read easily. This gives the animation software some responsibilities:
 1. Output the animations in a variety of formats: to a preview window, to a file, or output via serial. The animation file and serial formats need to agree between the microcontroller and the animation software, which means the people writing that software needed to plan this out
 2. Be able to switch between these output formats easily.
 3. We also anticipated having multiple ways to generate animations: programatically, from external drawing programs, or from splines. At the end of the day we only generated them from drawing programs, but this was an initial requirement that worked its way into our design.

To execute on this design we made the animation generator have a design with switchable "backends" and "frontends":
[![Backend and frontend design](../images/frontend_backend.jpg)](../images/frontend_backend.jpg)
(Click to enlarge)

We only ended up implemented the file-reading frontend, but we did have multiple backends that allowed us to view animations on the computer, stream over serial, and export to a file that could be loaded onto our SD card. We used the same format for streaming over serial and for writing to an output file, which allowed us to share a lot of code. The file format was, as mentioned above, a simple text-based format that we chose to avoid endianness and struct packing issues that can come with binary formants (unless you're careful about their implementation.) This isn't the most space-efficient format, but it's very easy to inspect and the code is easy for others to read. The easy inspection of the file output and the visual preview backend made it easy to insure this code was correct long before we had our microcontroller firmware working, which made final integration much smoother. Because of this modular system it was very easy to add file export and serial capabilities when we needed them, which was made integration go more smoothly.

We used OpenCV to read and display images. The rest of our code just used C++17 standard library features and the CMake build system.

<a id="budget"></a>

## Budget {{<navarrow Navigation>}}

Our total cost for our final display was **$231.13**. Below shows the breakdown by subsystem and item:

| Tank           | Cost          |
|----------------|---------------|
| Glass panes    | $6.30         |
| Acrylic spacer | $4*           |
| Delrin holders | $2*           |
| Epoxy          | $10.94        |
| Ferrofluid     | $31           |
| Ammonia        | $1.78          |
| **Total**      | **$56.12** |



| Magnets and Structures      | Cost       |
|-----------------------------|------------|
| 3D-printed pieces (< 200 g) | $5*        |
| Threaded inserts            | $6.93      |
| M3 screws                   | $5.33      |
| Steel dowels                | $20.76     |
| Magnet wire                 | $10*       |
| **Total**                   | **$48.02** |


| Electronics (Mouser Part Number)            | Cost       |
|---------------------------------------------|------------|
| Dupont socket/socket connectors (485-266)   | $11.85     |
| Pin headers (649-1012937891601BLF)          | $3.99      |
| Darlington transistor arrays (511-ULQ2801A) | $16.25     |
| LED Drivers (771-PCA9685BS118)              | $24.96     |
| 0.1 uF Capacitors (963-HMF212B7104KGHT)     | $2.80      |
| 10 uF Polar Capacitors (710-865080340001)   | $2.52      |
| 10k resistors (652-CR0603FX-1002ELF)        | $0.75      |
| **Total** (including tax/shipping)          | **$75.06** |


| Boards                   | Cost       |
|--------------------------|------------|
| Arduino Mega*            | $34.93     |
| Custom controller boards | $15        |
| Perfboard                | $2*        |
| **Total**                | **$51.93** |






\* Estimate (Obtained for Free)


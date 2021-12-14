---
title: "Systems"
description: "An overview of our ferrofluid project's journey"
draft: false
author:
  display_name: Ferrofluid Team
date: 2021-11-08
---

##### Contents: <a id="Navigation"></a>

- [Tank](#tank)
- [Magnets](#magnets)
- [Controller](#controller)
- [Firmware](#firmware)
- [Animation and Software](#animation)
- [Budget](#budget)

<a id="tank"></a>

## Tank 

Our tank is comprised of two sheets of 10" by 12" glass with thickness 3/32" separated by a 1/4" acrylic rim. They are attached with epoxy.

Next, the tank was cleaned thoroughly using ammonia and hot water and scrubbed with ??.


![cool_tank](../images/cool_tank.gif)

<a id="magnets"></a>

## Magnets

The first plan for team FerroFish was to use PCB magnets. However, upon testing the PCB magnets we found that they were not viable for lifting and moving ferrofluid so the decision was made to create our own electromagnets.

Electromagnets are created by wrapping wire around a ferrous core and applying a voltage to the wire, creating a current in the wire. The current induces a magnetic field and thus magnetizes the ferrous core - creating a magnet.

The equation for the strength of the field given by our electromagnets is below:

$B = \frac{\mu_oNI}{l}$

Where $\mu_o$ is the permittivity of free space, $N$ is the number of turns in the wire, $I$ is the current, and $l$ is the length of the solenoid.

Electromagnets are more flexible than permanent magnets because they can be easily turned on and off by adjusting voltage. As a team we decided that electromagnets would provide the flexibility.

##### Creating our Electromagnets

We decided for cost purposes we would create our own electromagnets rather than buying premade ones. We calculated that 1000 turns would create a magnetic field strong enough to lift the ferrofluid.

Creating our electromagnets was three main steps:
1. 3D print spools for winding
2. Create the magnets by winding the wire
3. Soldering jumper cables onto the magnets so they can be used with controller boards

##### 3D Printing Spools

The spools were printeed in two parts and then glued together. These spools were then mounted onto the wiring rig so wire could be wound onto them. 

![spool_cad](../images/spool_cad.png)

##### Winding the Wires

On the rig for winding the magnets there is a counter that let the winder know when 1000 turns had been reached. Our goal for the magnet grid was a 4x4 grid, or 16 total magnets. Extra spools were printed in the event we had magnets break.

##### Soldering the Magnets

Once the magnets were wound, jumper cables were soldered onto the ends of the wires. The connection between the wire and the jumper cable was then wrapped in a protective shrink wrap to prevent shorts with other wires. A finished magnet is pictured below.

[![magnet](../images/magnet.jpg)](../images/magnet.jpg)

##### Using the Magnets

We 3D printed a holder for our 4x4 magnet grid. This holder went through multiple iterations as we refined our tolerances and also created a way to hold the magnets to the tank. An image of all 16 magnets as well as the CAD for the final holder is below.

**INSERT IMAGE OF MAGNET HOLDER**
![magnet_holder_iso](../images/magnet_holder_iso.png)
**INSERT IMAGE OF MAGNET HOLDER CAD**
![magnet_holder_iso_lower](../images/magnet_holder_iso_lower.png)

![irl_magnet_holder](../images/irl_magnet_holder.png)


### Final Take-Aways

While originally we did not think that creating our own electromagnets would be cost or time effective, by the end of our project, it was apparent that it was our best option. 

Creating the magnets required a lot of patience and communication, but ultimately, it created a better end product as we were able to successfully make a magnet grid with them and lift the ferrofluid.




<a id="controller"></a>

## Controller

Put schematic here

[![controller_kicad](../images/controller_kicad.png)](../images/controller_kicad.png)

[![block_diagram](../images/block_diagram.jpg)](../images/block_diagram.jpg)

<a id="firmware"></a>

## Firmware



<a id="animation"></a>

## Animation and Software

<a id="budget"></a>

## Budget

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


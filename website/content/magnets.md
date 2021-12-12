---
title: "Electromagnets"
description: "An overview of our ferrofluid project's journey"
draft: false
author:
  display_name: Ferrofluid Team
date: 2021-11-08
---

# Creating Electromagnets

## Why Electromagnets?

The first plan for team FerroFish was to use PCB magnets. However, upon testing the PCB magnets we found that they were not viable for lifting and moving ferrofluid so the decision was made to create our own electromagnets.

Electromagnets are created by wrapping wire around a ferrous core and applying a voltage to the wire, creating a current in the wire. The current induces a magnetic field and thus magnetizes the ferrous core - creating a magnet.

The equation for the strength of the field given by our electromagnets is below:

$B = \frac{\mu_oNI}{l}$

Where $\mu_o$ is the permittivity of free space, $N$ is the number of turns in the wire, $I$ is the current, and $l$ is the length of the solenoid.

Electromagnets are more flexible than permanent magnets because they can be easily turned on and off by adjusting voltage. As a team we decided that electromagnets would provide the flexibility.

## Creating our Electromagnets

We decided for cost purposes we would create our own electromagnets rather than buying premade ones. We calculated that 1000 turns would create a magnetic field strong enough to lift the ferrofluid.

Creating our electromagnets was three main steps:
1. 3D print spools for winding
2. Create the magnets by winding the wire
3. Soldering jumper cables onto the magnets so they can be used with controller boards

### 3D Printing Spools

The spools were printeed in two parts and then glued together. These spools were then mounted onto the wiring rig so wire could be wound onto them. 

**INSERT IMAGE OF SPOOL CAD HERE**

### Winding the Wires

On the rig for winding the magnets there is a counter that let the winder know when 1000 turns had been reached. Our goal for the magnet grid was a 4x4 grid, or 16 total magnets. Extra spools were printed in the event we had magnets break.

### Soldering the Magnets

Once the magnets were wound, jumper cables were soldered onto the ends of the wires. The connection between the wire and the jumper cable was then wrapped in a protective shrink wrap to prevent shorts with other wires. A finished magnet is pictured below.

[magnet](static/images/magnet.jpg)

## Using the Magnets

We 3D printed a holder for our 4x4 magnet grid. This holder went through multiple iterations as we refined our tolerances and also created a way to hold the magnets to the tank. An image of all 16 magnets as well as the CAD for the final holder is below.

**INSERT IMAGE OF MAGNET HOLDER**
**INSERT IMAGE OF MAGNET HOLDER CAD**

From the holder we were able to connect all of the magnets to the controller board and turn them on and off via software.
**ADD LINK TO SOFTWARE PAGE?**

## Final Take-Aways

While originally we did not think that creating our own electromagnets would be cost or time effective, by the end of our project it was apparent that it was our best option. 

Creating the magnets required a lot of patience and communication, but ultimately it created a better end product as we were able to successfully make a magnet grid with them and lift the ferrofluid.

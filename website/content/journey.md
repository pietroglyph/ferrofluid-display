---
title: "Our Journey"
description: "An overview of our ferrofluid project's journey"
draft: false
author:
  display_name: Ferrofluid Team
date: 2021-12-13
mathjax: true
---

## Design Sprints

The duration of the project was broken up into three two-week-long design sprints. At the end of each sprint, we presented our progress to the teaching team and our peers.

##### Contents: <a id="Navigation"></a>
- [Sprint One](#SprintOne)
- [Sprint Two](#SprintTwo)
- [Sprint Three](#SprintThree)

---

{{<sprintsection One>}}

Sprint one info

##### What We Did:
###### Thing We Worked On:
Info about thing

###### Other Thing We Worked On:
Info about other thing
##### What We Learned:
Based on this thing, we decided to do this instead of that.

---

{{<sprintsection Two>}}

Due to a general feeling of being overwhelmed across the campus, the second sprint review presentation for our class was instead changed to a simple design-review chat with the teaching team. 

##### Spring Goals and Progress
Our initial goals for our second sprint were to:
- Finish construction of a leak- and stain-proof ferrofluid and water tank
- Finish assembly and characterization of the PCB electromagnets
- Design and order magnet controller PCBs
- Finish basic magnet control Arduino/Teensy firmware
- Begin animation generation code

###### Ferrofluid tank: 
At the end of our first sprint, our ferrofluid finally arrived. After conducting thorough research on how people online construct their ferrofluid tanks, we compiled a list of tips to constructing a stain-free ferrofluid tank:
- Use glass for the tank walls. If not available, then acrylic with a hydrophobic coating such as Rain-X may also work.
- Thoroughly clean tank walls, ideally with a harsh chemical such as ammonia or hydrochloric acid.
- After constructing the tank, fill it with brine and let it sit for at least 24 hours

Since we did not have access to sheets of glass, while having ready access to acrylic sheets via the Olin Shop, we started by constructing a small acrylic test tank. We also did not go thorugh the trouble of sourcing hydrochloric acid from the chemistry lab, so we ended up only following one and a half out of the three tips: letting the brine sit for 24 hours, and treating the sub-optimal acrylic with Rain-X. Thus, unfortunately but unsurprisingly, after treating our Acrylic tank with Rain-X and letting it wait 24 hours, we still found that it stained quite severly:

![stained_acrylic_tank](../images/stained_acrylic_tank.png)

This did not surprise us, as once again  we really were only following one and a half out of the three tips The first obvious next step from here was to construct a glass tank. After constructing the tank, treating with Rain-X, and letting it sit with brine for 24 hours, we added in the ferrofluid, and unfortunately found that it still stains:
![stained image](../images/stained_tank.jpg)

By this time, we had reached the end of our sprint. Thus, we failed to meet our sprint goal of having a leak- and stain-proof ferrofluid and water tank by the end of our second sprint. We only had one more thing to try next sprint: cleaning the glass using harsh chemicals.

###### PCB electromagnets:
During this spring, our PCB electromagnets had arrived. Our PCB electromagnets had ~60 turns per coil, per PCB. Naively, we thught that since magnetic field strenght was proportional to turn count, we would be able to just stack the PCBs until we reached enough field strength to move the ferrofluid. Thus, when the boards arrived, we soldered them together using our pre-made solder pads and a reflow oven:

Soldered PCB Stack             |  PCB Coils holding paperclips
:-------------------------:|:-------------------------:
![pcb_coil_stack](../images/pcb_coil_stack.jpg)  |  ![pcb_coil_test](../images/pcb_coil_test.jpg)

Unfortunately, our assumption about being able to stack the coils for additional strength did not hold true, so our PCB electromagnets proved too weak. Reality was, since field strength $B = \frac{\mu_0}{l}NI$, and really, if you have some $\hat{r}$ resistance per turn, then $I = \frac{V}{\hat{r}N}$. Notice then, that when we multiply this $I$ with $N$, the $N$ and denominator of $I$ cancel out, meaning that turn count does not actually affect the strength of a magnet, since an increase in turn count would be counterracted by a corresponding decrease in current. With this limitation in mind, we now have thoughts on how to redesign our PCB electromagnets to achieve suitable strength for moving the ferrofluid, but we do not have enough time to actually go through with that redesign.

In conclusion, at the end of the sprint, while we had reached our goal of assembling and characterizing our PCB electromagnets, we have found that they are not strong enough, and we will need to look for an alternative for sourcing our electromagnets.
###### Magnet Controller board:
During this sprint, we designed, reviewed, and ordered our magnet controller board design. While our design is largely similar to that of other Ferrofluid tank projects online, the exact parts used are not available in the exact same package or SKUs, so we had to make substitutions of our own, and verify by comparing datasheets to make sure that our substitutions are suitable.

Controller PCB Design Render             | Fully Assembled Controller Board 
:-------------------------:|:-------------------------:
![controller_render](../images/controller_render.png)  |  ![controller_physical](../images/controller_physical.png)

With this, we met our sprint goal of finishing the design and ordering of magnet controller boards.

###### LED test grid / Firmware:
During this sprint, we constructed an LED test grid array that consisted of two 4x4 groups of LEDs that were individually addressable. This was to assist in developing a first past at the controlling firmware and testing LED addressing.

![led_grid](../images/led_grid.jpg)

###### Animation code engine
At the end of Sprint 2, we had finished a first path for both "frontend" and "backend" for the software. For the frontend, we had created a C++ program that will convert a set of PNG files to a simple file export with duty cycles corresponding to each pixel location. For the backend, a basic plotter was created.

###### Website
At the end of Sprint 2, we set up the basic layout and structure for our final website.

##### What We Learned:
At the end of Sprint 2, we were feeling very low: our tank was staining quite heavily, and our PCB electromagnets were not nearly strong enough. However, during this process we learned that if we want to build a stain-resistant ferrofluid tank, we really would have to treat the glass with harsh chemicals. At the same time, we learned that for an electromagnet coil made with the same material, the turn count ultimately does not affect the strength, as the effects are negated by the drop in current.

----

{{<sprintsection Three>}}

Sprint three summary

##### What We Did:
###### Thing We Worked On:
Info about thing

###### Other Thing We Worked On:
Info about other thing
##### What We Learned:
Based on this thing, we decided to do this instead of that.

----

Requirements

Your final project site is required to contain the following elements.

A high level summary description of the project’s objectives
* Review/edit as needed

~~A system diagram depicting the schematic relationships between all of the different subsystems comprising your final system.~~
* Review/let Lila know what edits to make

~~An account of how you spent your $250 budget. You must include all components and materials and their estimated costs (even if you obtained them for free somehow). Please note where something was obtained for free and cost is just your best estimate.~~
* Done

~~A detailed description of electrical design (circuit diagrams are appropriate) and any necessary analysis.~~
* Review/edit as needed (v possible i missed something)

A detailed description of your mechanical design ~~(CAD images/renderings are appropriate)~~ and any necessary analysis.
* Not sure how much is done

~~A detailed description of the firmware design with links to complete source code (github or other repository is helpful)~~.
* Review/edit as needed 

~~A detailed description of software design with links to complete source code (github or other repository is helpful). Please be sure to include a list of all external software dependencies (eg. OpenCV, Google Voice API, etc.)~~
* Were dependencies included? Review/edit as needed

~~Photos or videos of your final system in action.~~
* Added/consider adding more

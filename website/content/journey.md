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

Sprint One had three main objectives:

 - Create a test tank
 - Research magnets
 - Ordering important materials and other important organizing tasks

### Test Tank
Creating the test tank had two subgoals: creating an "etch-a-sketch" where we were able to move metal shavings with an electromagnet and creating a water-tight tank.

#### Etch-A-Sketch
We were able to successfully create a small test tank that only had metal shavings in it. We used an electromagnet that had previously been purchased to prove that the metal shavings could be moved with an electromagnet. An image of the test tank is below.

![metal shaving tank](../images/steel_dust_model.jpg)

#### Water-Tight Tank
Another goal with tank ideation was to begin thinking about what it would take to create a water-tight tank. At the start we knew that the finished product would have ferrofluid suspended in saline,  so we had to be prepared to reach that goal.

When we made the tank it was apparent that there were issues with leaking, a evidenced by salt build up on the outside of the tank from the saline inside. An image of the salt build up is below.

![Salt](../images/Salt_build_Up.JPG)

Additionally, we were unsure if we had successfully coated the tank to be hydrophobic. If the inside of the tank was not properly cleaned and coated, the ferrofluid would stick to the glass and stain it.

### Magnet Research
We started this sprint by researching whether or not we should wind electromagnets by hand or buy them. We quickly ruled out buying electromagnets as it would be too expensive to buy the amount we wanted and we ruled out winding our own because of the time commitment it required.

#### Wound Electromagnet Research
In our research, we realized that outright buying electromagnets would be too expensive. At the time we also discussed winding our own electromagnets, but ruled that out because of the time commitment and  potentially having costs regarding wiring get out of hand.

However, we did hand-wind a couple electromagnets to test if it was feasible. They were much weaker than our final magnets would be, but were an important test. 

During this sprint we settled on a different way to create an electromagnet: PCB coils.

#### PCB Coil Electromagnets
We designed and ordered PCB capable of creating an electromagnet. We believed our PCB electromagnets would have  many advantages over traditional electromagnets: we could fit more "turns" in the wire in less space, power and control the magnets more easily, and we could cover more area of the tank.  A picture of one of the finished magnet boards is below.

![mag board](../images/PCB_Mag.jpg)

We designed and ordered the boards this sprint. Ideally they would work like a regular electromagnet - current would pass through the coils and magnetize a ferrous core in the middle of the turns. The plan was to cut small piece of a metal rod and slot them into the holes in the PCB.

### Organization
We made important organizational leaps during this sprint as well: we ordered the ferrofluid, we placed a Home Depot order with many crucial items, and we created a Notion board to delegate tasks.

The ferrofluid arrived at the very end of sprint one, so we were able to begin preliminary tests with it immediately. We ordered glass for a larger tank, epoxy, and a metal rod (ferrous core for the magnets) from Home Depot, which allowed us to fully begin tank prototyping. Additionally, we learned how to communicate better as a team during this sprint, a skill that would serve us well in the future.

### What We Learned
During this sprint we hit a few snags. In particular we were struggling to create a water-tight tank and we had some concerns about the PCB magnets we had ordered. It would take multiple iterations before we were able to successfully create a water-tight tank, and we had to wait to receive the PCB to see if our reservations would come to fruition.

We also learned how to communicate with each other and plan ahead. Using Notion to delegate tasks and keep track of notes was extremely helpful and at the end of the sprint we were more secure in our planning and more prepared to present for sprint two.

### Next Steps
We decided the following would be deliverables for sprint two:

 - Create a working, stain-proof ferrofluid tank
 - Control and characterize the PCB magnets
 - Complete magnet control software and begin working on animation software

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

Sprint three was focused on getting a working MVP and creating viable backup plans. Our main goals were to:
 
 - Brainstorm permanent magnet based display alternatives in case the ferrofluid tank wouldn't be ready in time
 - Design parts to hold everything together
 - Finish up the animation software

### Permanent-Magnet-Based Display Alternatives
Since we were having so much trouble with the ferrofluid staining the tank, we needed a backup plan.
#### Koi Pond
One of the alternatives was a "Koi Pond" design, where the grid of electromagnets would lay flat and move a permanent magnet like a fish in a pond. A sketch of the concept is below:

![koi pond idea sketch](../images/koi_pond_sketch.png)

#### Pillars
Another alternative was a design we called "pillars", where the electromagnets lift permanent magnets on pillars to create patterns.

### Spool Holder
We created a 3D-printed part to hold the electromagnets in place against the tank. This took a couple of iterations to get right, since we had to hold everything securely while leaving room to route the wires. The two pieces are held together with screws and heat-set threaded inserts. Images of the parts are below:

![magnet holder lower](../images/magnet_holder_iso_lower.png)
![magnet holder](../images/magnet_holder_iso.png)

### Tank Breakthrough
We managed to get a tank that wouldn't leak or stain after thorough cleaning, so ferrofluid was a go. This involved a **lot** of iteration with beakers that we tried cleaning with different combinations of ammonia and eventually Goof Off. When we got down a formula that seemed to work (ammona, scrub, Goof Off, scrub, let saline sit in beaker briefly), we tried it on the tank. This failed, which we think was because we weren't able to scrub the tank enough or possibly because there was some contamination in one of the beakers we used to mix saline. We we-washed and re-scrubbed the tank and added saline and it worked. This became our final tank. We were able to successfully test our hand-wound magnets with the ferrofluid tank, and it worked great--they were much easier to move than the iron powder.

### Software
The software was almost done - animations could be created with an online tool, exported as keyframes, and turned into a file to put on an SD card for the microcontroller. Then, the microcontroller would interpolate animations and send commands to the PWM ICs on the controller boards.

### What We Learned
This sprint was mostly grinding out various clearly defined tasks. We continued to improve communication, and managed to get our MVP working with a little bit of time to spare.

Even though we didn't end up needing to use them, we agreed that the backup plans were good to have, but we could've been more organized about figuring out proof-of-concepts.

### Next Steps
In the final few days before our demonstration, we had a couple of goals in mind:

- Wire up all 16 magnets to the magnet controller board
- Create a set of animations to use on demo day

If we found extra time, we were also thinking of setting up a smaller power supply, since we had been using a benchtop one the whole time.
  
# Demo Day Deliverables
For demo day our goals were as follows:
  - Wire all 16 magnets to the controller board
  - Create animations for the demo
  
We were able to successfully wire up all of the magnets, create a stand to hold the magnets and other components behind the tank, and load animations onto an SD card and play them on the tank. Our system was in full working order for demo day and a video of the working tank is below. A video of a working animation is below.
  [video](https://youtu.be/yQUrwy7noX4)
  
----

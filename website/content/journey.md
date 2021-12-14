---
title: "Our Journey"
description: "An overview of our ferrofluid project's journey"
draft: false
author:
  display_name: Ferrofluid Team
date: 2021-12-13
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

Sprint two info (talk about how it's a check-in instead of a sprint)

##### What We Did:
###### Thing We Worked On:
Info about thing

###### Other Thing We Worked On:
Info about other thing
##### What We Learned:
Based on this thing, we decided to do this instead of that.

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
We managed to get a tank that wouldn't leak or stain after thorough cleaning, so ferrofluid was a go. We were able to successfully test our hand-wound magnets with the ferrofluid tank, and it worked great.

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

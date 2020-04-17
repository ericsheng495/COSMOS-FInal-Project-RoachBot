# COSMOS-FInal-Project-RoachBot
## Overview 
Our goal is to be able to reliably get through the obstacle field and move on to the next section.



## Events and Services 
The Events-and-Services Paradigm: Unlike  many other programming lanugages, C doesn't have a built in asynchronous behavior.  "Asynchronous code" is written in “services” which execute in reaction to "events". Events are detected by using several static variables to compare the previous status of the roach and comparing its current status. If it's different, it returns that an event has occurred and calls the service to complete the event. If not, it displays that nothing has occurred. 
Ultimately, this allows us to write code for many different behaviors that can execute at the same time.


## State Machine
A state is a temporary but not instantaneous property of a system.
Ex: Solid, liquid, gas
A state machine is a set of states that are connected by transitions. A transition is usually an event.

### Our States 
1. **Moving Forward:** Both motors move forward at the same speed.
2. **Arc_Right:** The robot follows the right wall after the right bumper is pressed.
3. **Arc_Left:** The robot’s left bumper is pressed, making it turn until the right bumper is pressed
4. **Turn_Right:** The robot turns around a corner to keep on following the right wall.
5. **Timed_Move_Forward:** The robot moves forward for a certain amount of time once the Island Timer expires.
6. **Hiding:** The robot stops moving when it reaches a dark spot.

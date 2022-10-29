# Introduction to Robotics (2022 - 2023)

This repo contains laboratory homeworks for the Introduction to Robotics course, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

## Homework 1

### Task:
Use a separat potentiometer in controlling each of thecolor of the RGB led (Red, Green and Blue). The control must be done with digital electronics(it must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.

### Photos:
https://imgur.com/a/iaK2B8A

### Video:
https://www.youtube.com/watch?v=XTkY4eXRiVw

## Homework 2

### Task:
Building the traffic lights for a crosswalk.It will use 2 LEDs to represent the traffic lights for people (red and blue, because I don't have another green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).See the states it needs to go through.

The system has the following states:

State 1(default, reinstated after state 4 ends):  green light for cars, red  light  for  people,  no  sounds.   Duration:  indefinite,  changed  bypressing the button.

State 2(initiated by counting down 8 seconds after a button press):the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds.Duration:  3 seconds.

State 3(initiated after state 2 ends):  red for cars, green for peopleand a beeping sound from the buzzer at a constant interval. Duration:8 seconds.

State 4(initiated after state 3 ends):  red for cars,blinking greenfor people and a beeping sound from the buzzer,  at a constant in-terval,  faster than the beeping in state 3.  This state should last 4 seconds.

Pressing  the  button  in  any  state  other  than  state  1  should NOT yield any actions.

### Photos:
https://imgur.com/a/rxVOya5

### Video:
https://www.youtube.com/watch?v=N21eQ5cNmFc

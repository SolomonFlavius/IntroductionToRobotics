# Introduction to Robotics (2022 - 2023)

This repo contains laboratory homeworks for the Introduction to Robotics course, taken in the 3rd year at the Faculty of Mathematics and Computer Science, University of Bucharest. Each homework includes requirements, implementation details, code and image files.

## Homework 1

### Task:
Use a separat potentiometer in controlling each of thecolor of the RGB led (Red, Green and Blue). The control must be done with digital electronics(it must read the value of the potentiometer with Arduino, and write a mapped value to each of the pins connected to the led.

### Photos:
![poza1](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework1/WhatsApp%20Image%202022-10-25%20at%2020.54.48.jpeg)
![poza2](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework1/WhatsApp%20Image%202022-10-25%20at%2020.54.49%20(1).jpeg)
![poza3](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework1/WhatsApp%20Image%202022-10-25%20at%2020.54.49.jpeg)

### Video:
https://www.youtube.com/watch?v=XTkY4eXRiVw

## Homework 2

### Task:
Building the traffic lights for a crosswalk.It will use 2 LEDs to represent the traffic lights for people (red and blue, because I don't have another green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).See the states it needs to go through.

The system has the following states:

State 1(default, reinstated after state 4 ends): green light for cars, red light for people, no sounds. Duration: indefinite, changed by pressing the button.

State 2(initiated by counting down 8 seconds after a button press): the light should be yellow for cars, red for people and no sounds. Duration: 3 seconds.

State 3(initiated after state 2 ends): red for cars, blue(I really need to find a green LED) for people and a beeping sound from the buzzer at a constant interval. Duration: 8 seconds.

State 4(initiated after state 3 ends):  red for cars, blinking blue(please imagine is green) for people and a beeping sound from the buzzer, at a constant interval,  faster than the beeping in state 3. This state should last 4 seconds.

Pressing the button in any state other than state 1 should NOT yield any actions.

### Photos:
![poza1](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework2/Homework%202%20-%20Imgur%20(1).jpg)
![poza2](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework2/Homework%202%20-%20Imgur%20(2).jpg)
![poza3](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework2/Homework%202%20-%20Imgur%20(3).jpg)
![poza4](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework2/Homework%202%20-%20Imgur.jpg)

### Video:
https://www.youtube.com/watch?v=N21eQ5cNmFc

## Homework 3

### Task:
This will use the joystick to control the position of the segment and ”draw” on the display. The movement between segments should be natural (meaning they should jump from the current position only to neighbors, but without passing through ”walls”.

The system has the following states:

1. State 1 (default, but also initiated after a button press in State 2): 

Current position blinking. Can use the joystick to move from one position to neighbors. Short pressing the button toggles state 2. Long pressing the button in state resets the entire display by turning all the segments OFF and moving the current position to the decimal point.

2. State 2 (initiated after a button press in State 1): The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the X (or Y, you chose) axis should change the segment state from ON to OFF or from OFF to ON. Clicking the joystick should save the segment state and exit back to state 1.

### Photos:
![poza1](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework3/WhatsApp%20Image%202022-11-06%20at%2016.27.07%20(1).jpeg)
![poza2](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework3/WhatsApp%20Image%202022-11-06%20at%2016.27.07.jpeg)
![poza3](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework3/WhatsApp%20Image%202022-11-06%20at%2016.27.08.jpeg)


### Video:
https://youtu.be/gUyym5VYDh8

## Homework 2

### Task:
Building the traffic lights for a crosswalk.It will use 2 LEDs to represent the traffic lights for people (red and blue, because I don't have another green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green).See the states it needs to go through.

The system has the following states:

State 1(default, reinstated after state 4 ends): green light for cars, red light for people, no sounds. Duration: indefinite, changed by pressing the button.

State 2(initiated by counting down 8 seconds after a button press): the light should be yellow for cars, red for people and no sounds. Duration: 3 seconds.

State 3(initiated after state 2 ends): red for cars, blue(I really need to find a green LED) for people and a beeping sound from the buzzer at a constant interval. Duration: 8 seconds.

State 4(initiated after state 3 ends):  red for cars, blinking blue(please imagine is green) for people and a beeping sound from the buzzer, at a constant interval,  faster than the beeping in state 3. This state should last 4 seconds.

Pressing the button in any state other than state 1 should NOT yield any actions.

### Photos:
![poza1](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework2/Homework%202%20-%20Imgur%20(1).jpg)
![poza2](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework2/Homework%202%20-%20Imgur%20(2).jpg)
![poza3](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework2/Homework%202%20-%20Imgur%20(3).jpg)
![poza4](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework2/Homework%202%20-%20Imgur.jpg)

### Video:
https://www.youtube.com/watch?v=N21eQ5cNmFc

## Homework 4

### Task:
Use the joystick to move through the 4 digit 7 segment displays digits, press the button to lock in on the current digit and use the other axis to increment or decrement the number. Keep the button pressed to reset all the digit values and the current position to the first digit in the first state. The system has the following states:

1.First state: Use a joystick axis to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. When pressing the button, locks in on the selected digit and enter the second state.

2.Second state: In this state, the decimal point stays always on, no longer blinking and no longer can use the axis to cycle through the 4 digits. Instead, using the other  axis,  you  can  increment or decrement  the  number  on  the  current  digit  IN  HEX. Pressing the button again returns to the previous state.

### Photos:
![poza1](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework4/1.jpg)
![poza2](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework4/2.jpg)
![poza3](https://github.com/SolomonFlavius/IntroductionToRobotics/blob/main/homework4/3.jpg)


### Video:
https://www.youtube.com/shorts/oLV0Uxn-Poo

## Matrix Project(in progress) - Snake
Will be updated with full project

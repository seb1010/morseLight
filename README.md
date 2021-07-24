# Text to Morse Code

## Project Overview

In this project I made a light blink in morse code. You are able to write to a text file and the corresponding morse code will show on the light. Input length was restricted by the program memory of the microcontroller.

## Implementation
*WRITE ABOUT HOW PARTS CONNECTED*

### Microcontroller
**Name:** ATTiny13
**Memory:**
**More Specifications:**

### Programming Languages Used
* C
    ** Converting text to binary code, expressed in hexadecimal
    ** ` insert C file name `
    ** Hexadecimal file could be read directly by assembler
    ** Insert conversion image
* Assembly (for ATTiny13)
    ** Used to instruct microcontroller to flash lights
    ** ` insert .s file here `
    ** WRITE ABOUT REGISTERS IF YOU FEEL LIKE IT
    ** Pulse with Modulation(PWM): microcontroller has built in PWM
        *** Accidentally chose pins with no built in PWM
        *** To remedy this, simply implemented PWM in assembly 

### PCB

Single sided, I etched the PCB at home. Mixed through-hole and surface mount parts. 

* Insert image*

#### Layout
Talk about if you feel like it

* insert image *


### Schematic 
* figure out why switch then give brief description* 

#### Components
* 1 transistor
* 5 LED's
* 1 potentiometer

## Project Result and Takeaways

### Results
It worked! You were able to write in a text file and have the message flash on the LED. 
* insert link to video or image * 

### Takeaways
I learned to check if pins were PWM
If I were to do this project again I would modify hardware instead of software to deal with PWM error. (Explain more cuz i no know)
I was able to work on my skills combining different programs to integrate.
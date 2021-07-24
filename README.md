# Text to Morse Code

## Project Overview

In this project I made a light blink in morse code. You are able to write to a text file and the corresponding morse code will show on the light. PWM was used to when turning on and off light for smooth transitions. Input length was restricted by the program memory of the microcontroller. There is also a switch to turn off the morse code and keep the light on all the time.

## Implementation
*WRITE ABOUT HOW PARTS CONNECTED*

### Microcontroller
**Name:** ATTiny13
**Memory:** 1k of program memory

### Dimming
	** I wanted to be able to control the maximum brightness of the light so it could be used durring the day or at night.
    ** With only 8 bits of PWM on the microcontroller this would be impossible to achieve while keeping the transitions looking smooth even at low brightnesses. 
    ** This is why I included the potentiometer and transitor
    ** It isn't a perfect circuit as it is tempurature sensitive and sensitive to changes in supply voltage, but I wasn't able to notice these issues when using the light.

### Programming Languages Used
* C
    ** Converting text to a binary code (morse code), expressed as hex in a ascii file.
    ** `textToMorse.c`
    ** This output file can be read directly by the assembler I used (avra)
    ** The assembler wrote the binary code into the program memory

* Assembly (for ATTiny13)
    ** loads one byte at a time from the program memory
    ** then sends one bit at a time to a pin using PWM to soften transitions
    ** `morseOut.asm`
    ** Pulse with Modulation(PWM): microcontroller has built in PWM
        *** Accidentally chose pins with no built in PWM
        *** To remedy this, implemented PWM in software

### PCB
I etched the PCB at home. Mixed through-hole and surface mount parts. 

* Insert image* 

#### Components
* 1 transistor
* 5 LED's
* 1 potentiometer

## Project Result and Takeaways

### Results
It worked ok. Storing morse code the way I did was not space efficient for long messages. Also the c program was very sensitive to white space, so you have to be carful with formatting. That could definitly use improvement.
* insert link to video or image * 

### Takeaways
I learned to know your parts
If I were to do this project again I would modify the pcb instead of software to deal with PWM error. I knew I was only making one so it seemed like a more eligant solution to keep the pcb intact, but now I dont think that was the best option. 
I was able to work on my skills combining different programs to integrate.

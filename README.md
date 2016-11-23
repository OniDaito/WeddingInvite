# WeddingInvite
This repository contains the code and the schematics for the Wedding InvitationI built and sent out to various people.

It is based on the Nokia 5110 screen and the ATTiny85. It is possible to flash the ATTiny85 with your own programs and use the breakout pins to control other things.

## Hardware and software details

The chip is an [ATTiny85]() programmed with AVRDUDE. I use a buspirate to program my chip. You can use an Arduino and the arduino software to do this, but I found that a lot more hassle. The makefile included in this project should do it all for you, so long as you have gcc, avr-gcc and avrdude installed. Using ubuntu, you can install these packages quite easily.

The invite marks the screen pins and not the ATTiny. So if you want to flash the tiny, you need to start with the pin marked GND and work down from there. Here are the mappings

    Invite ATTiny
    
    GND -> GND (Pin 4)
    PB5 -> RESET (Pin 1)  
     -> MOSI (Pin 5) 
     -> MISO (Pin 6)
     -> CLK  (Pin 7)
    VCC -> VCC (Pin 8)

With these linked up, flashing the chip should be a doddle. Take a look at the makefile I've written for an example of how to compile up your AVR C program and flash it to the chip.

## Credits

A lot of the code came from [http://thegaragelab.com/nokia-5110-lcd-displays-on-the-attiny/](http://thegaragelab.com/nokia-5110-lcd-displays-on-the-attiny/) so big thanks to them.

The images for the intro were created by [Lucy Blundell](https://twitter.com/Kinmoku87) who is fab!

[Phil Eagleton](http://voltsport.co.uk/) helped make sure I was thorough in my hardware debugging.

Finally, the lovely [Charles Yarnold](https://hackaday.io/Solexious) gave me some good suggestions on the hardware.



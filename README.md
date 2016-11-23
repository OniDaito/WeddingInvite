# WeddingInvite
This repository contains the code and the schematics for the Wedding Invitation I built and sent out to various people.

It is based on the Nokia 5110 screen and the ATtiny85. It is possible to flash the ATtiny85 with your own programs and use the breakout pins to control other things.

## Hardware and software details

The chip is an [ATtiny85](http://www.atmel.com/devices/ATTINY85.aspx) programmed with [AVRDUDE](http://www.nongnu.org/avrdude/). I use a buspirate to program my chip. You can use an Arduino and the arduino software to do this, but I found that a lot more hassle. The makefile included in this project should do it all for you, so long as you have gcc, avr-gcc and avrdude installed. Using any Linux flavour (I personally used Arch), you can install these packages quite easily.

The invite marks the screen pins and not the ATTiny. So if you want to flash the tiny, you need to start with the pin marked GND and work down from there. Here are the mappings

    Invite    ATTiny          BusPirate
    ------    ------          ---------
    GND   ->  GND   (Pin 4)   Black
    PB5   ->  RESET (Pin 1)   Red
    RST   ->  MOSI  (Pin 5)   Pink
    DC    ->  MISO  (Pin 6)   Brown
    DIN   ->  CLK   (Pin 7)   Yellow
    VCC   ->  VCC   (Pin 8)   White (3V)

With these linked up, flashing the chip should be a doddle. Take a look at the makefile I've written for an example of how to compile up your AVR C program and flash it to the chip.

I use RS Components' [Design Spark](https://www.rs-online.com/designspark/home) for creating the PCB and schematics. I find it a little easier than [Eagle](https://cadsoft.io/) though it helps to have a good guide.

## Credits

A lot of the code came from [http://thegaragelab.com/nokia-5110-lcd-displays-on-the-attiny/](http://thegaragelab.com/nokia-5110-lcd-displays-on-the-attiny/) so big thanks to them.

The images for the intro were created by [Lucy Blundell](https://twitter.com/Kinmoku87) who is fab!

The mighty [Phil Eagleton](http://voltsport.co.uk/) helped make sure I was thorough in my hardware debugging and helped teach me the hidden gem that is Design Spark.

Finally, the lovely [Charles Yarnold](https://hackaday.io/Solexious) gave me some good suggestions on the hardware.

I've previously used [DirtyPCB]() to have my boards made but if you want a professional eye to check your boards and you like things to be made in the UK, then [Quick-teck](http://www.quick-teck.co.uk/index.php) are the people for you.

The parts are largely sourced from RS Components - in particular their Bow branch here in London. These folks are lovely. 


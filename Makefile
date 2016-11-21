#!/bin/bash
all:
	avr-gcc -I./include/ src/invite.c src/softspi.c src/smallfont.c -Os -o invite.elf -mmcu=attiny85
	avr-objcopy -O ihex invite.elf invite.rom
	sudo avrdude -c buspirate -p t85 -P /dev/ttyUSB0 -U flash:w:invite.rom -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m -v -u
	#sudo avrdude -c buspirate -p t85 -P /dev/ttyUSB0 -U flash:w:invite.rom -v -u

test:
	avr-gcc -I./include/ src/test.c -Os -o test.elf -mmcu=attiny85
	avr-objcopy -O ihex test.elf test.rom
	sudo avrdude -c buspirate -p t85 -P /dev/ttyUSB0 -U flash:w:test.rom -v

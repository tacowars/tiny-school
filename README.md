Tiny School
-----------

This is an AVR-GCC C project for the Atmel [attiny85](http://www.atmel.com/devices/attiny85.aspx).
Mainly I'm trying out I2C libraries and learning the
ins and outs of the peripherals on the tiny85.


### TODO
- hook internal temp again under a new register
- low power, sleep until master calls?
- servo
- refactor
- ~~get remote LED blinking~~


### NOTES
- pull-ups are 4k7
- TWI works with single bytes at a time
- reading clears the register

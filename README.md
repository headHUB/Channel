# Channel
Serial communication between microcontrollers and/or computers.
Library works on both sides using exactly the same c++ syntax.
Handles encapsulation of any data structure, object oriented, easy to read and
to use.
# Requirements
- Arduino compatible board with at least one HardwareSerial

The following is only needed to let your microcontroller communicate with your
computer:
- Unix like os (Tested on Mac OSX and Linux)
- know how to cd in a terminal
- know how to use g++ to compile your programs and link compiled libraries

# Installation
1. Clone or download as zip and unpack to your Arduino IDE libraries folder.

2. In order to let your microcontroller communicate with your
computer, compile my modified version of [Tod E. Kurt](http://todbot.com/blog)'s
 arduino-serial-lib:
from a terminal, within the pc-serial directory enter
```
gcc -o arduino-serial-lib.o -c arduino-serial-lib.c
```

# Running my example
The following example will send two integers from your computer terminal to
the arduino in the form of a struct via an instance of the Channel class. When
Arduino gets your data it calls the "reply" function. This simply computes the
division and sends the result back trough another instance of Channel. The
computer side displays the result and asks for more input.

**After trying this please remember to report feedback! Thank you**

1. Open arduino IDE, go to *File > examples > Channel > serial_calculator*, and
upload it to your arduino, make sure the serial monitor is closed.

2. Open serial_calculator.cpp from the pc-examples folder with any text editor,
on line 12 replace `/dev/cu.usbmodem14131` with the name of the serial port your
board is attached to (it appears at the bottom of all Arduino IDE windows) then
save your change.

3. From a terminal, in the pc-examples folder enter
```
g++ -o serial_calculator serial_calculator.cpp ../pc-serial/arduino-serial-lib.o
```
4. Then execute by entering:
```
./serial_calculator
```
5. When prompted enter integers followed by Enter, you should get back the
result of the division.

# API
To better understand the API please look at the Channel.h file and read the
examples, feel free to ask any questions.

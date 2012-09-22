=================================
Test code for the 
  Illinois Tech Robotics 
    Roomba Shield (Arduino Mega)
=================================

As the title says, this is test code for the Arduino Mega Roomba Shield
designed for the Illinois Tech Robotics Club (ITR). It takes the form of
an Arduino sketch (roombashield_testi2c.ino) but please note that it is
written without the use of any Arduino functions -- only avr-libc standard
library functions are used. The Arduino environment is used only to compile
and upload.

Hardware documentation will be forthcoming, but the following functions
have been tested so far:

- LEDs, RGB LED
- LM75B temp sensor
- BMP085 humidity sensor (raw data only)
- HMC5883 magnetometer (not yet implemented here however)
- L3G4200 3-axis gyro (basic setup)
- LIS3DH 3-axis accel (basic setup)
- AT45DB081D Flash (see roombashield_testflash, needs correct page size)

Basic Roomba functions have also been verified (not in this sketch):

- Baud rate change
- Various modes, including sleep
- Drive command

===================
Basic usage
===================

See the .ino file. Most of the shield functions are in "roombashield.h",
with byte-by-byte serial functions in "basicserial.h".
After calling a setup function, the main loop looks for a character coming
into the USB serial console (57600 baud). 

=======================
Technical notes / Todo
=======================

The I2C could use some restructuring; it's all copy/pasted in bulk from
the avr-libc examples.

See the respective header files for setup information on the gyro and
accelerometer.

=======================
Legal (BSD License)
=======================

Copyright (c) 2012 Mike Ng <mng2@iit.edu>

I2C guts are from avr-libc:

Portions of avr-libc are Copyright (c) 1999-2005
Keith Gudger,
Bjoern Haase,
Steinar Haugen,
Peter Jansen,
Reinhard Jessich,
Magnus Johansson,
Artur Lipowski,
Marek Michalkiewicz,
Colin O'Flynn,
Bob Paddock,
Reiner Patommel,
Michael Rickman,
Theodore A. Roth,
Juergen Schilling,
Philip Soeberg,
Anatoly Sokolov,
Nils Kristian Strom,
Michael Stumpf,
Stefan Swanepoel,
Eric B. Weddington,
Joerg Wunsch,
Dmitry Xmelkov,
The Regents of the University of California. 
All rights reserved.

Portions of avr-libc documentation Copyright (c) 1990, 1991, 1993, 1994
The Regents of the University of California.
All rights reserved.


   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. 


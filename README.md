SantaHatDemo
============
This program uses Energia to spice up a Santa hat for the holidays using an MSP430F5529 LaunchPad! This santa hat plays holiday songs and blinks a strip of LEDs synched with the music and a spinning fur ball on the hat using the grove servo!

To install this, download the folder, unzip and rename the folder inside of the master folder from 
SantaHatDemo-master to just SantaHatDemo Drag this file into your ~/Energia where the rest of your projects
are and place it there. Go into the folder and double click SantaHatDemo.ino and it will open in energia.

It is important to note that you will also need to take the servo.cpp file and replace the current one used. This is due to a collision between the tone library in energia and the servo library. They both use Timer A native to the MSP430F5529 LaunchPad. To account for this, the new servo.cpp file uses TimerB instead. 

IT IS IMPORTANT TO NOTE THAT IF YOU DO THIS, YOUR SERVO WILL NOT WORK ANYMORE ON ANY MSP430G2 DEVICES DUE TO THE FACT THEY ONLY HAVE ONE TIMER (TIMER A).

Servo File Edit Work-along
Take the Servo.cpp file and replace the current Servo.cpp file in your file path. For example mine is: C:\Users\a0221660\Documents\energia-0101E0013\hardware\msp430\libraries\Servo 
Place the file there and replace it with the old one. 


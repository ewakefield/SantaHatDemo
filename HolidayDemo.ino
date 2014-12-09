/* 
 * Author: Evan Wakefield
 * Modified code from Raj Madhuram and Tom Igoe
 * 
 * There are places in the code that held passwords and vital information that is unique to each user.
 * Please read through the code and place your own passwords and tokens. All places to replace or change are denoted by XXXX's or "Place your account/key info here"
 * Depending on use, you might have to change a few other things as well. Thanks! Enjoy!
 *
 * HolidayDemo.ino
 *
 *      Created on: Nov 29, 2014
 *      Author: a0221660@ti.com
 *
 *      Copyright (c) 2014, Evan Wakefield
 *		All rights reserved.
 *
 *		Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *		1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 *		2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the
 *                 documentation and/or other materials provided with the distribution.
 *
 *		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 *		EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *		OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *		SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 *		OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *		HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *		(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *		EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#include "pitches.h"
#include "LPD8806.h"
#include <Servo.h>
#include <SPI.h>

Servo myservo;

int pos = 0;

// Number of RGB LEDs in strand:
int nLEDs = 32;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 14;
int clockPin = 15;
int toneNum = 0;  
int randomOffset = 0;
int outputStartPin = 3;
int tracker1 = 0;

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);


typedef struct {
   int *melody;
   int *durations;
   int numCount;
   int tempo;
   int low, high;
} tune;

tune tunes[5];

// Jingle Bells
int jingleBells[] = { N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
                      N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_E5, N_D5, N_D5, N_E5, N_D5, N_G5,
                      N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_E5, N_G5, N_C5, N_D5, N_E5,
                      N_F5, N_F5, N_F5, N_F5, N_F5, N_E5, N_E5, N_E5, N_G5, N_G5, N_F5, N_D5, N_C5};
int jingleBellsDurations[] = { 4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
                               4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8,
                               4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16,
                               4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16 };
                               
// The first noel

int firstNoel[] = { N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
                    N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
                    N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4,
                    N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4,
                    N_E4, N_E4, N_D4, N_C4, N_D4, N_E4, N_F4, N_G4, N_C5, N_B4, N_A4, N_A4,
                    N_G4, N_C5, N_B4, N_A4, N_G4, N_A4, N_B4, N_C5, N_G4, N_F4, N_E4
                  };

int firstNoelDurations[] = { 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
                             8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                             8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 4, 4, 4,
                             8, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4,                             
                             8, 2, 2, 6, 2, 2, 2, 8, 2, 2, 8, 4,
                             12, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8  };
                             
// O Holy Night

int oHolyNight[] = { N_E4, N_E4, N_E4, N_G4, N_REST, N_G4, N_A4, N_A4, N_F4, N_A4, N_C5,
                     N_G4, N_G4, N_E4, N_D4, N_C4, N_E4, N_F4, N_G4, N_F4, N_D4, N_C4,
                     N_E4, N_E4, N_E4, N_G4, N_REST, N_G4, N_A4, N_A4, N_F4, N_A4, N_C5,
                     N_G4, N_G4, N_FS4, N_E4, N_B4, N_G4, N_A4, N_B4, N_C5, N_B4, N_E4, N_REST, N_G4,
                     N_G4, N_A4, N_D4, N_G4, N_A4, N_G4, N_C5, N_E4, N_A4, N_G4, N_G4, N_G4, N_A4,
                     N_D4, N_G4, N_A4, N_G4, N_C5, N_E4, N_G4, N_C5, N_C5, N_B4, N_A4,
                     N_B4, N_A4, N_REST, N_A4, N_D5, N_D5, N_A4, N_A4, N_A4, N_C5,
                     N_C5, N_REST, N_C5, N_E5, N_D5, N_D5, N_G4, N_C5, N_C5, N_B4, N_A4,
                     N_G4, N_G4, N_G4, N_A4, N_G4, N_G4, N_G4, N_C5, N_D5,
                     N_D5, N_G4, N_E5, N_E5, N_D5, N_C5, N_B4, N_C5, N_D5,
                     N_C5 };

int oHolyNightDurations[] = { 6, 4, 2, 8, 2, 2 , 4, 2, 4, 2, 12,
                              4, 2, 4, 2, 6, 4, 2, 6, 4, 2, 24,
                              6, 4, 2, 8, 2, 2 , 4, 2, 4, 2, 12,
                              4, 2, 4, 2, 6, 4, 2, 6, 4, 2, 20, 2, 2,
                              6, 6, 6, 6, 4, 2, 4, 2, 6, 4, 2, 6, 6,
                              6, 6, 4, 2, 4, 2, 12, 12, 6, 4, 2,
                              12, 8, 2, 2, 12, 4, 2, 4, 2, 12,
                              8, 2, 2, 12, 8, 2, 2, 12, 6, 4, 2,
                              12, 4, 2, 4, 2, 12, 6, 6, 12,
                              6, 6, 12, 6, 6, 12, 6, 4, 2,
                              24 };
//we three kings

int weThreeKings[] = { N_B4, N_A4, N_G4, N_E4, N_FS4, N_G4, N_FS4, N_E4,
                       N_B4, N_A4, N_G4, N_E4, N_FS4, N_G4, N_FS4, N_E4,
                       N_G4, N_G4, N_G4, N_A4, N_A4, N_B4, N_B4, N_D5, N_C5, N_B4,
                       N_A4, N_B4, N_A4, N_G4, N_FS4, N_E4,
                       N_FS4, N_A4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4,
                       N_G4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_B4, N_G4, N_G4, N_G4, N_D4, N_G4, N_E4, N_G4 };
                       
int weThreeKingsDurations[] = { 4, 2, 4, 2, 2, 2, 2, 6,
                                4, 2, 4, 2, 2, 2, 2, 6,
                                2, 2, 2, 4, 2, 4, 2, 2, 2, 2,
                                2, 2, 2, 4, 2, 6,
                                6, 6, 4, 2, 4, 2, 4, 2, 6, 4, 2, 4, 2, 4, 2, 6,
                                4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 4, 2, 6  };
  
// What child is this

int whatChild[] = { N_E4, N_G4, N_A4, N_B4, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_B3, N_REST,  N_E4,
                    N_G4, N_A4, N_B4, N_C4, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4, N_REST,
                    N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_E4, N_E4, N_DS4, N_E4, N_FS4, N_DS4, N_B3, N_REST, 
                    N_D5, N_D5, N_C5, N_B4, N_A4, N_FS4, N_D4, N_E4, N_FS4, N_G4, N_FS4, N_E4, N_DS4, N_CS4, N_D4, N_E4, N_E4} ;

int whatChildDurations[] = { 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 6, 2, 2, 2,
                             4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4, 2,
                             6, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 3, 1, 2, 4, 2, 4, 2,
                             6, 3, 1, 2, 4, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 6, 4};
  

//functions to switch lights from red to green and green to red. 
void go1(){
  int i;
      for(i=0; i<strip.numPixels(); i++){
        if(i%2==0){
          shiftColorRed(i);
        }
        else{
          shiftColorGreen(i);
        }
      }
}
//functions to switch lights from red to green and green to red. 
void go2(){
  int i;
      for(i=0; i<strip.numPixels(); i++){
        if(i%2==0){
          shiftColorGreen(i);
        }
        else{
          shiftColorRed(i);
        }
      }
}
//changes color of LEDs to red
void shiftColorRed(int i){
  strip.setPixelColor(i,strip.Color(127,0,0));
  strip.show();
}
//changes color of LEDs to green
void shiftColorGreen(int i){
  strip.setPixelColor(i,strip.Color(0,127,0));
  strip.show();
}
//flips the colors in one quick function; tracker1 is used to control flip of red to green green to red
void flip(){
  if(tracker1==0){
    go1();
    tracker1 = 1;
  }
  else{
    go2();
    tracker1 = 0;
  }
}
//plays tune
void play(int tuneNum) {
  
  randomOffset = random(32);
    
  int numNotes = tunes[tuneNum].numCount;
  int tempo = tunes[tuneNum].tempo;
  for (int thisNote = 0; thisNote < numNotes; thisNote++) {
    
    int freq = tunes[tuneNum].melody[thisNote]*2;
    int noteDuration = tempo*tunes[tuneNum].durations[thisNote];
    
    if (freq > 0) {
       int n = (map(freq, tunes[tuneNum].low, tunes[tuneNum].high, 1, 31) + randomOffset)%31 + 1; 
       tone(8, freq, noteDuration);       
    } else {
       // REST
       delay(noteDuration);
    }

    delay(noteDuration);
    
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 0.10;    
    delay(pauseBetweenNotes);    
    Serial.println("hey");
    noTone(8);
    flip();
  }  
}

void playTune() {
  play(toneNum);
  toneNum = (toneNum+1)%5;//steps through tunes
}

void setup() {
  
  Serial.begin(9600);
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
  
  int numTunes = 5;
  
  tunes[0].melody = jingleBells;
  tunes[0].durations = jingleBellsDurations;
  tunes[0].numCount = sizeof(jingleBells)/sizeof(int);
  tunes[0].tempo = 60;
  
  tunes[1].melody = firstNoel;
  tunes[1].durations = firstNoelDurations;
  tunes[1].numCount = sizeof(firstNoel)/sizeof(int);  
  tunes[1].tempo = 60;
  
  tunes[2].melody = oHolyNight;
  tunes[2].durations = oHolyNightDurations;
  tunes[2].numCount = sizeof(oHolyNight)/sizeof(int);    
  tunes[2].tempo = 100;
  
  tunes[3].melody = weThreeKings;
  tunes[3].durations = weThreeKingsDurations;
  tunes[3].numCount = sizeof(weThreeKings)/sizeof(int);      
  tunes[3].tempo = 100;
  
  tunes[4].melody = whatChild;
  tunes[4].durations = whatChildDurations;
  tunes[4].numCount = sizeof(whatChild)/sizeof(int);      
  tunes[4].tempo = 100;  
  
  for (int i=0; i<numTunes; i++) {
    int low = N_DS8;
    int high = 0;
    for (int j=0; j<tunes[i].numCount; j++) {
      int freq = tunes[i].melody[j];
      if (freq != 0 && freq<low) low = freq;
      if (freq>high) high = freq;
    }
    tunes[i].high = high;
    tunes[i].low = low;
  }
  myservo.attach(12);
  
}

void loop() {
    playTune();
    //spins servo during tune switch
    for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
    for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    }  
}

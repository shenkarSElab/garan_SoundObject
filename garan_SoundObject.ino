
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Garan.h"
#include <Wire.h>
#include "Adafruit_LSM303.h"

#if !defined(__MSP430_CPU__)
SoftwareSerial garanSerial(8, 9); // RX, TX
#endif

Garan player(garanSerial);
//A4(SDA) A5(SCL)
Adafruit_LSM303 lsm;


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);

  }


  Serial.println("Console is ready!");
  Play (); 
} 

void loop() {

  Accelo();
  int volXval = ((int)lsm.accelData.x);
  int outputXValue = map(volXval, 1024,-1024, 0, 15); 
  player.setVolume(outputXValue);
  playermenu () ;

}

void Play (){

  if (garanSerial.available()) {   
    unsigned char recvByte = garanSerial.read();
    //  if (recvByte == 0x24) Serial.println();

    //    Serial.print(String(recvByte, HEX) + " ");
  }

  player.singleLoopName("1.mp3");

}

void Accelo (){
  lsm.read();
  Serial.print("X: "); 
  Serial.print((int)lsm.accelData.x); 
  Serial.print(" ");
  Serial.print("Y: "); 
  Serial.print((int)lsm.accelData.y);     
  Serial.print(" ");
  Serial.print("Z: "); 
  Serial.println((int)lsm.accelData.z);   
  Serial.print(" ");

}

void  playermenu (){

  if (Serial.available()) {  

    switch(Serial.read()) {

    case '4':
      player.singlePlayName("1.mp3");
      break;
    case '5':
      player.sequencePlayName("1.mp3");
      break;
    case '6':
      player.singleLoopName("1.mp3");
      break;
    case '9':
      player.setVolume(15);
      break;
    case '0':
      player.setVolume(0);
      break;      
    case 'f':
      player.feedbackAtEnd();
      break;
    case ']':
      player.volumeUp();
      break;
    case '[':
      player.volumeDown();
      break; 
    default:
      Serial.println("This key maps to none.");     
    }
  }

}


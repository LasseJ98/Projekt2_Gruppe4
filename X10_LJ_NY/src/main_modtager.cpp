/*#include <Arduino.h>
#include "X10_Modtager.h"


X10_Modtager HouseA;
byte modtaget;

void setup() {
  HouseA.initX10_modtager(19,2);
  HouseA.initZeroCrossInterrupt_Modtager();
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(19,INPUT);
  Serial.begin(9600);

}

void loop() 
{
  while (HouseA.checkStartCode() != true)
  {
  }

     digitalWrite(LED_BUILTIN,HIGH);

}*/
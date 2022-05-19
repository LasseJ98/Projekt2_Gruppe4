#include <Arduino.h>
#include "Led.h"
#include "X10_Modtager.h"

//Defining pins
#define RX_PIN 19
#define ZERO_PIN 2
#define LED_PIN 13

//Index definitions
#define UNIT_INDEX 0
#define COMMAND_INDEX 1

//Object declarations
Led led(LED_PIN);
X10_Modtager HouseA;
//ID deklarations
byte unitId = 0b01101001; //TODO: FIND ID 
//Read data
byte * readDataPtr = new byte[2];

void setup() {
  HouseA.initX10_modtager(RX_PIN,ZERO_PIN);
  HouseA.initZeroCrossInterrupt_Modtager();
  Serial.begin(9600);
}

void loop() {

if (HouseA.receiveCommands() == unitId)
{
   Serial.print("\nDET VIRKER");
  led.setPWM(100);
}

  //  readDataPtr = &HouseA.receiveCommands();
  
  // if( readData[UNIT_INDEX] == unitId)
  // {
  //   led.chooseBrightness(readData[COMMAND_INDEX]);
  // }

}
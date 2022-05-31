#include <Arduino.h>
#include "Led.h"
#include "X10_Modtager.h"

//Defining pins
#define RX_PIN 19
#define ZERO_PIN 2
#define LED_PIN 13


//ON/OFF
#define ON_PWM 100
#define OFF_PWM 0

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
volatile int *pointer;

void setup() {
  HouseA.initX10_modtager(RX_PIN,1);
  HouseA.initZeroCrossInterrupt_Modtager();
  Serial.begin(9600);

}

void loop() {
  pointer = HouseA.receiveCommands();
  
  if (pointer[0] == unitId)
  {
    if (pointer[1] == ON_PWM)
    {
      Serial.print("\nLED'en er ON");
      led.setPWM(100);
    }
    else if(pointer[1] == OFF_PWM)
    {
      Serial.print("\nLED'en er ON");
      led.setPWM(0);
    }
  }
  
  
  


}


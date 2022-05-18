#include <Arduino.h>
#include "led.h"
#include "X10_Modtager.h"

#define RX_PIN 18
#define ZERO_PIN 4
#define LED_OUT 9

Led led;
X10_Modtager HouseA;
byte unitId = 0b01101001;
unsigned int currentFunction;

void setup() {
  // put your setup code here, to run once:
  HouseA.initX10_modtager(RX_PIN,ZERO_PIN);
  led.init(LED_OUT);

}

void loop() {
  
  int *commands = HouseA.receiveCommands();

  if(commands[0] == unitId)
  {
    analogWrite(LED_OUT, HIGH);
  }

}
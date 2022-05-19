#include <Arduino.h>
#include "X10_Sender.h"

X10_Sender HouseA;

void setup()
{
  HouseA.initX10(1, 2, 5);
  pinMode(LED_BUILTIN, OUTPUT);
  HouseA.initZeroCrossInterrupt_Sender();
  pinMode(8, INPUT);
}

void loop()
{

  
  if (digitalRead(8) == 0)
  {
    HouseA.sendStartCode();
    HouseA.sendHouseA();
    HouseA.sendUnit(1);
    HouseA.sendSuffixUnit();

    // HouseA.countZeroCross(6);

    // HouseA.sendStartCode();
    // HouseA.sendHouseA();
    // HouseA.sendFunction(1);
    // HouseA.sendSuffixFunction();
    delay(5000);

    // HouseA.sendCommand(1,1);

  }
  
  

}

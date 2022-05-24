#include <Arduino.h>
#include "X10_Sender.h"

X10_Sender HouseA;

void setup()
{
  HouseA.initX10(1);
  pinMode(LED_BUILTIN, OUTPUT);
  HouseA.initZeroCrossInterrupt_Sender();
  pinMode(8, INPUT);
  HouseA.configMorning(1,1,0,0,0,0,0,0,0,0,0,0);
  HouseA.configEveningRoutine(1,1,0,0,1,1,0,0,0,0,0,0);
}
 
void loop()
{ 
    //HouseA.sendCommand(1,1);
    HouseA.sendStartCode();
    //HouseA.sendUnit(1);
}


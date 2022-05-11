/*#include <Arduino.h>
#include "X10_Sender.h"

X10_Sender HouseA;

void setup() 
{
  HouseA.initX10(18,2,4);
}


void loop() 
{
    //HouseA.sendCommand(1,1);
    HouseA.sendUnit(1);
    //HouseA.sendStartCode();
    delay(50);

    //HouseA.sendHouseA();
}\*

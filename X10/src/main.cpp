#include <Arduino.h>
#include "X10.h"

X10 HouseA;

void setup() 
{
  HouseA.initX10(18,2,4);
}


void loop() 
{
    HouseA.sendCommand(1,1);
    
    delayMicroseconds(500000);
}

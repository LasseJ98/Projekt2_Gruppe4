
#include <Arduino.h>
#include "X10_Sender.h"

X10_Sender HouseA;

void setup() 
{
  HouseA.initX10(18,4,3)); //TX_pin,zero-pin & burst_pin 
}


void loop() 
{
    //HouseA.sendCommand(1,1);
    HouseA.sendUnit(1);
    //HouseA.sendStartCode();
    delay(50);

    //HouseA.sendHouseA();
}

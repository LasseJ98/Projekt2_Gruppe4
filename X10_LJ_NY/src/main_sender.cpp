#include <Arduino.h>
#include "X10_Sender.h"

X10_Sender HouseA;

void setup()
{
  HouseA.initX10(1);
  pinMode(LED_BUILTIN, OUTPUT);
  HouseA.initZeroCrossInterrupt_Sender();
  pinMode(8, INPUT);
  pinMode(11, INPUT);
  HouseA.configMorning(1,1,0,0,0,0,0,0,0,0,0,0);
  HouseA.configEveningRoutine(1,1,0,0,1,1,0,0,0,0,0,0);
  
}
 
void loop()
{ 
    
    
        if (digitalRead(8) == HIGH)
        {
          HouseA.sendCommand(1,1);      
        }
        if (digitalRead(9) == HIGH)
        {
          HouseA.sendCommand(2,1);      
        }
    
    
}


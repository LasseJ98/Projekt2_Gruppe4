/*#include <Arduino.h>
#include "X10_Sender.h"

X10_Sender HouseA;

void setup()
{
  HouseA.initX10(1, 2, 5);
  pinMode(LED_BUILTIN, OUTPUT);
  HouseA.initZeroCrossInterrupt_Sender();
}

void loop()
{
 
  HouseA.countOneZeroCross();

  while (1)
  {
      HouseA.sendStartCode();
  }
  

}*/

#include <Arduino.h>
#include "led.h"
#include "X10_Modtager.h"

Led led;
X10_Modtager HouseA;

void setup() {
  // put your setup code here, to run once:
  
  led.init();
}

void loop() {
  
  led.setPWM(100);
  delay(500);
  led.setPWM(50);
  delay(500);
  led.setPWM(10);
  delay(500);
}
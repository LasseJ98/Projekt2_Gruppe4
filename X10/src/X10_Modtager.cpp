#include "X10_Modtager.h"
#include <Arduino.h>

#define HIGH 0x1
#define LOW  0x0
#define BIT_Read_DELAY 7333
#define BIT_LENGTH 950	

void X10_Modtager::initX10_modtager(int rx_pin, int zero_pin)
{
    rx_pin_ = rx_pin;
    zero_pin_ = zero_pin;

   pinMode(rx_pin_, INPUT);
   pinMode(zero_pin_, INPUT);
}


bool X10_Modtager::checkStartCode()
{
    byte startcode = 0b1110;
    byte readingBit = 0b0000;

    while (digitalRead(rx_pin_) != 0)
    {
       for (size_t i = 1; i <= 4; i++)
       {
           readingBit |= (digitalRead(rx_pin_) << i); 
           delayMicroseconds(BIT_LENGTH);
           delayMicroseconds(BIT_Read_DELAY);
           if (readingBit == startcode)
           {
               return true;
           } 
       }
    }
}

byte X10_Modtager::checkHouseA(byte rx_pin)
{
    
}

uint16_t X10_Modtager::checkUnit(byte rx_pin)
{

}

uint16_t X10_Modtager::checkFunction(byte rx_pin)
{

}

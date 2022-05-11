#include "X10_Modtager.h"
#include <Arduino.h>

#define HIGH 0x1
#define LOW  0x0
#define BIT_Read_DELAY 7333
#define BIT_LENGTH 950	

#define UNIT[2] = {0b0110100101,0b1010100101};
#define UNIT2 0b1010100101
#define ON 0b0101100110
#define OFF 0b0101101010



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

byte X10_Modtager::checkHouseA()
{
     byte HouseA = 0b01101001;
     byte readingBit = 0b00000000;

       for (size_t i = 1; i <= 8; i++)
       {
           readingBit |= (digitalRead(rx_pin_) << i); 
           delayMicroseconds(BIT_LENGTH);
           delayMicroseconds(BIT_Read_DELAY);
       }

    return readingBit;
}

uint16_t X10_Modtager::checkUnit()
{
    uint16_t readingBit = 0b0000000000;

       for (size_t i = 1; i <= 8; i++)
       {
           readingBit |= (digitalRead(rx_pin_) << i); 
           delayMicroseconds(BIT_LENGTH);
           delayMicroseconds(BIT_Read_DELAY);
       }

    return readingBit;
}

uint16_t X10_Modtager::checkFunction()
{
    uint16_t readingBit = 0b0000000000;

       for (size_t i = 1; i <= 8; i++)
       {
           readingBit |= (digitalRead(rx_pin_) << i); 
           delayMicroseconds(BIT_LENGTH);
           delayMicroseconds(BIT_Read_DELAY);
       }

    return readingBit;
}

int X10_Modtager::receiveCommands()
{
   uint16_t unit[2] = {0b0000000000,0b0000000000};
   uint16_t function[2] = {0b0000000000,0b0000000000};

   
   for (size_t i = 0; i <= 1; i++)
   {
       while (checkStartCode() != true)
        {
        //Lav ingenting
        }

        checkHouseA();
        unit[i] = checkUnit();
   }
    
   for (size_t i = 0; i <= 1; i++)
   {
       while (checkStartCode() != true)
       {
        // Lav ingenting
       }

       checkHouseA();
       function[i] = checkFunction();
   }
    
    uint16_t unit_result;
    uint16_t function_result;

    for (size_t i = 0; i <= 1; i++)
    {
        uint16_t unit_temp = unit[i];
        uint16_t function_temp = function [i];
        

        for (size_t i = 0; i <= 1; i++)
        {
            if (unit_temp == unit[i])
            {
                unit_result = unit_temp;
            }
            if (function_temp == function[i])
            {
                function_result = function_temp;
            } 
        }       
    }

    return function_result + unit_result;
}

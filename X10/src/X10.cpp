#include "X10.h"
#include <Arduino.h>

#define HIGH 0x1
#define LOW  0x0
#define BIT_DELAY 2338
#define BIT_LENGTH 950		

#define UNIT1 0b01100
#define UNIT2 0b11100
#define UNIT3 0b00100
#define UNIT4 0b10100
#define UNIT5 0b00010

#define ON 0b00101
#define OFF 0b00111

void X10::initX10(int tx_pin, int zero_pin, int burst_pin)
{
    tx_pin_ = tx_pin;
    zero_pin_ = zero_pin;
   pinMode(tx_pin_, OUTPUT);
   pinMode(zero_pin, INPUT);
   pinMode(burst_pin,tx_pin_);
   
}

void X10::countZeroCross(int count)
{
    int counter;

    for (size_t i = 1; i <= count; i++)
    {
        if (digitalRead(zero_pin_) == RISING || digitalRead(zero_pin_) == FALLING)
        {
            counter++;
            delayMicroseconds(BIT_LENGTH);
        }  
    }
}

void X10::sendStartCode()
{
    byte startcode = 0b1110;
    int bit_size = 4;

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = startcode & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.
        delayMicroseconds(BIT_LENGTH); //Vent 950 us.
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countZeroCross(1); //Vent 1 zero-cross.
    }
}

void X10::sendCommand(byte House_code,byte Unit, byte Function)
{
    sendStartCode();

    sendHouse





    
}

void X10::sendHouseA()
{
    byte HouseA = 0b01101001;
    int bit_size = 8;

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = HouseA & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.
        delayMicroseconds(BIT_LENGTH); //Vent 950 us.
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countZeroCross(1); //Vent 1 zero-cross.
    }
}

void X10::sendUnit(int unit)
{


}



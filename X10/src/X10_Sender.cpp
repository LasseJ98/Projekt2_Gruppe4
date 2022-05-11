#include "X10_Sender.h"

#define HIGH 0x1
#define LOW  0x0
#define BIT_DELAY 7333
#define BIT_LENGTH 1000		

#define UNIT1 0b01100
#define UNIT2 0b11100
#define UNIT3 0b00100
#define UNIT4 0b10100
#define UNIT5 0b00010

#define ON 0b00101
#define OFF 0b00111

void X10_Sender::initX10(int tx_pin, int zero_pin, int burst_pin)
{
    tx_pin_ = tx_pin;
    zero_pin_ = zero_pin;
    burst_pin_ = burst_pin;
   pinMode(tx_pin_, OUTPUT);
   pinMode(zero_pin_, INPUT);
   pinMode(burst_pin_,OUTPUT);

}

void X10_Sender::countZeroCross(int count)
{
    int counter;

    for (size_t i = 1; i <= count; i++)
    {
        if (digitalRead(zero_pin_) == RISING || digitalRead(zero_pin_) == FALLING)
        {
            counter++;
            delayMicroseconds(BIT_DELAY);
        }  
    }
}

void X10_Sender::sendStartCode()
{
    byte startcode = 0b1110;
    int bit_size = 4;

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = startcode & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.
        digitalWrite(burst_pin_, finalBit); //Burst et 1-tal
        delayMicroseconds(BIT_LENGTH); //Vent 950 us.
        digitalWrite(burst_pin_, LOW); //Sluk for burst
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countZeroCross(1); //Vent 1 zero-cross.
    }
}

void X10_Sender::sendCommand(int Unit, int Function)
{
    //Første sending af Adresse:
    sendStartCode();
    sendHouseA();
    sendUnit(Unit);

    //Anden sending af Adresse:
    sendStartCode();
    sendHouseA();
    sendUnit(Unit);

    //Vent 6 zerocrosses:
    countZeroCross(6);

    //Første sending af Command:
    sendStartCode();
    sendHouseA();
    sendFunction(Function);

    //Anden sending af Command:
    sendStartCode();
    sendHouseA();
    sendFunction(Function);
   
}

void X10_Sender::sendHouseA()
{
    byte HouseA = 0b01101001;
    int bit_size = 8;

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = HouseA & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.
        digitalWrite(burst_pin_, finalBit); //Burst et 1-tal
        delayMicroseconds(BIT_LENGTH); //Vent 950 us.
        digitalWrite(burst_pin_, LOW); //Sluk for burst
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countZeroCross(1); //Vent 1 zero-cross.
    }
}

void X10_Sender::sendUnit(int unit)
{
    int array_Var = unit_Array[unit-1];
    int bit_size = 10;

   for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = array_Var & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.
        digitalWrite(burst_pin_, finalBit); //Burst et 1-tal
        delayMicroseconds(BIT_LENGTH); //Vent 950 us.
        digitalWrite(burst_pin_, LOW); //Sluk for burst
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countZeroCross(1); //Vent 1 zero-cross.
    } 
}

void X10_Sender::sendFunction(int function)
{
    int function_Var = (function <= 1 && function >= 4 ? function_Array[function-1] : function_Array[1]);

    int bit_size = 10;

   for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = function_Var & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.
        digitalWrite(burst_pin_, finalBit); //Burst et 1-tal
        delayMicroseconds(BIT_LENGTH); //Vent 950 us.
        digitalWrite(burst_pin_, LOW); //Sluk for burst
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countZeroCross(1); //Vent 1 zero-cross.
    } 
}



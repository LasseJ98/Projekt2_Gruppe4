#include "X10.h"


#define HIGH 0x1
#define LOW  0x0
#define BIT_DELAY 2338
#define BIT_LENGTH 800		


#define HOUSEA 0b0110

#define UNIT1 0b01100
#define UNIT2 0b11100
#define UNIT3 0b00100
#define UNIT4 0b10100
#define UNIT5 0b00010

#define ON 0b00101
#define OFF 0b00111

void initX10(int tx_pin, int zero_pin)
{
    tx_pin_ = tx_pin;
    zero_pin_ = zero_pin;

   pinMode(tx_pin_, OUTPUT);
   pinMode(zero_pin, INPUT);
}

void countZeroCross(int count)
{
    int counter;

    for (size_t i = 1; i <= count; i++)
    {
        if (digitalRead(zero_pin) == LOW)
        {
            counter++;
            delayMicroseconds(BIT_LENGTH);
        }  
    }
    return
}

void sendCommand(byte House_code,byte Unit, byte Function)
{

}
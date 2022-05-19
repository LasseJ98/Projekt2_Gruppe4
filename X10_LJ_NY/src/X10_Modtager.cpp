#include "X10_Modtager.h"


#define HIGH 0x1
#define LOW  0x0
#define BIT_Read_DELAY 6.108
#define BIT_LENGTH 1	

//#define UNIT[2] = {0b0110100101,0b1010100101};
#define UNIT2 0b1010100101
#define ON 0b0101100110
#define OFF 0b0101101010

volatile int zero_detected_modtager;

void X10_Modtager::initWaitTime()
{
    TCNT3 = 65536-(8); //Venter 500 us.
    TCCR3A = 0b00000000;
    TCCR3B = 0b00000101;
    
    while ((TIFR3 & (1<<0)) == 0)
    {
        //Vent her
    }

    //Sluk clocken:
    TCCR3B = 0b00000000;
    //Reset Overflow:
    TIFR3 = 0b00000001;
}

void X10_Modtager::initZeroCrossInterrupt_Modtager()
{
    sei();
    EIMSK |= 0b00000010;
	EICRA = 0b00000100;
}

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


    while (digitalRead(rx_pin_) != HIGH)
    {
       //Vent til den går højt
    }

    Serial.print("Ny omgang: \n");
    unsigned long currenttime = 0;
    unsigned long eventtime = 980;
    for (size_t i = 4; i > 0; i--)
    {
        //Serial.println(digitalRead(rx_pin_));
        readingBit |= (digitalRead(rx_pin_) << (i-1));
        
        countOneZeroCross();
        //initWaitTime();
        currenttime = 0;
        currenttime = micros();

        while (micros() > currenttime + eventtime)
        {
            /* code */
        }
        
    
    }
    
    Serial.print(readingBit);

    if (readingBit == startcode)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

byte X10_Modtager::checkHouseA()
{
     //byte HouseA = 0b01101001;
     byte readingBit = 0b00000000;

       for (size_t i = 1; i <= 8; i++)
       {
           readingBit |= (digitalRead(rx_pin_) << i); 
         
       }

    return readingBit;
}

uint16_t X10_Modtager::checkUnit()
{
    uint16_t readingBit = 0b0000000000;

       for (size_t i = 1; i <= 8; i++)
       {
           readingBit |= (digitalRead(rx_pin_) << i); 
           
       }

    return readingBit;
}

uint16_t X10_Modtager::checkFunction()
{
    uint16_t readingBit = 0b0000000000;

       for (size_t i = 1; i <= 8; i++)
       {
           readingBit |= (digitalRead(rx_pin_) << i); 
           
       }

    return readingBit;
}

int* X10_Modtager::receiveCommands()
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

    //Vent 6 zerocrosses:
   for (size_t i = 0; i < 6; i++)
   {
      countOneZeroCross();
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
    
    //Vent 6 zerocrosses:
   for (size_t i = 0; i < 6; i++)
   {
      countOneZeroCross();
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

    static int return_array[2] = {function_result,unit_result};

    return return_array;
}


void X10_Modtager::countOneZeroCross()
{

    while (zero_detected_modtager != 1)
    {
            //Lav ingenting.
    }

    //Nulstiller Zero_detected:
    zero_detected_modtager = 0;

}

ISR(INT1_vect)
{
    zero_detected_modtager = 1;
}
#include "X10_Modtager.h"


#define HIGH 0x1
#define LOW  0x0

//#define UNIT[2] = {0b0110100101,0b1010100101};
#define UNIT2 0b1010100101
#define ON 0b0101100110
#define OFF 0b0101101010

volatile int zero_detected_modtager;


void X10_Modtager::initZeroCrossInterrupt_Modtager()
{
    sei();
    EIMSK |= 0b00000010;
	EICRA = 0b00000100;
}

void X10_Modtager::initX10_modtager(int rx_pin)
{
    rx_pin_ = rx_pin;

   pinMode(rx_pin_, INPUT);
}


bool X10_Modtager::checkStartCode()
{
    uint8_t startcode = 0b00001110;
  
    while (digitalRead(rx_pin_) != HIGH)
    {
        /* code */
    }
    
    countOneZeroCross();
    delayMicroseconds(450);
    rollingByteStart_ <<= 1;

    if (digitalRead(rx_pin_) == HIGH)
    {
        rollingByteStart_++;
    }
    
    rollingByteStart_ &= 0b00001111;

    if (rollingByteStart_ == startcode)
    {
        return true;
    }

   return false;
}

bool X10_Modtager::checkHouseA()
{
    uint8_t houseCodeA = 0b01101001;
    
    countOneZeroCross();
    delayMicroseconds(450);
    rollingByteHouse_ <<= 1;

    if (digitalRead(rx_pin_) == HIGH)
    {
        rollingByteHouse_++;
    }

    if (rollingByteHouse_ == houseCodeA)
    {
        return true;
    }
    
    
   return false;
}

bool X10_Modtager::checkUnit()
{
    uint8_t unitCode = 0b01101001;
    
    countOneZeroCross();
    delayMicroseconds(450);
    rollingByteUnit_ <<= 1;

    if (digitalRead(rx_pin_) == HIGH)
    {
        rollingByteUnit_++;
    }
    
    if (rollingByteUnit_ == unitCode)
    {
        return true;
    }

   return false;
}

bool X10_Modtager::checkUnitSuffix()
{
    uint8_t suffix = 0b00000001;
    
    countOneZeroCross();
    delayMicroseconds(450);
    rollingByteSuffixUnit_ <<= 1;

    if (digitalRead(rx_pin_) == HIGH)
    {
        rollingByteSuffixUnit_++;
    }
    
    rollingByteSuffixUnit_ &= 0b00000011;

    if (rollingByteSuffixUnit_ == suffix)
    {
        return true;
    }

   return false;

}

bool X10_Modtager::checkFunctionSuffix()
{
     uint8_t function_suffix = 0b00000010;
    
    countOneZeroCross();
    delayMicroseconds(450);
    rollingByteSuffixUnit_ <<= 1;

    if (digitalRead(rx_pin_) == HIGH)
    {
        rollingByteSuffixUnit_++;
    }
    
    rollingByteSuffixUnit_ &= 0b00000011;

    if (rollingByteSuffixUnit_ == function_suffix)
    {
        return true;
    }

   return false;

}

bool X10_Modtager::checkFunction()
{
    uint16_t readingBit = 0b0000000000;

       for (size_t i = 1; i <= 8; i++)
       {
           readingBit |= (digitalRead(rx_pin_) << i); 
           
       }

    return readingBit;
}

int* X10_Modtager::receiveCommands(int unit, int function)
{
    int8_t unit_temp = unit_Array[unit-1];
    int8_t function_temp = function_Array[function-1];
    static int return_array[2];

    if (rollingByteStart_ == 0b1110)
    {
        /* code */
    }
    else if (checkStartCode() == true)
    {
        Serial.print("\nStartcode godkendt\n");
    }
    else
    {
        return 0;
    }

    if (rollingByteHouse_ == 0b01101001)
    {
      
    }
    else if (checkHouseA() == true)
    {
        Serial.print("\nHouseCode godkendt\n");
    }
    else
    {
      return 0;
    }

    if (rollingByteUnit_ == unit_temp)
    {
        /* code */
    }
    else if (checkUnit() == true)
    {
        Serial.print("\nUnitCode godkendt\n");
    }
    else
    {
        return 0;
    }

    if (rollingByteSuffixUnit_ == 0b0001)
    {
        /* code */
    }
    else if (checkUnitSuffix() == true)
    {
        Serial.print("\nUnit Suffix godkendt\n");
    }
    else
    {
        return 0;
    }

    if (rollingByteFunction_ == function_temp)
    {
        /* code */
    }
    else if (checkFunction() == true)
    {
        Serial.print("\nFunction godkendt\n");

    }
    else
    {
        return 0;
    }

    if (rollingByteSuffixFunction_ == 0b0010)
    {
        /* code */
    }
    else if (checkFunctionSuffix() == true)
    {
        Serial.print("\nFunction Suffix godkendt\n");
        return_array[0] = unit_temp;
        return_array[1] = function_temp;

        return return_array;
    }
    else
    {
        return 0;
    }

    
  
  rollingByteStart_ = 0;
  rollingByteHouse_ = 0;
  rollingByteUnit_ = 0;
  rollingByteSuffixUnit_ = 0;
  rollingByteFunction_ = 0;
  rollingByteSuffixFunction_ = 0;
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
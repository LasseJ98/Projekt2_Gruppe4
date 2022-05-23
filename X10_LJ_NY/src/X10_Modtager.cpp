#include "X10_Modtager.h"


#define HIGH 0x1
#define LOW  0x0

volatile int zero_detected_modtager;

void X10_Modtager::initZeroCrossInterrupt_Modtager()
{
    //Aktiver interrupts:
    sei();
    //Tænd for Int1:
    EIMSK |= 0b00000010;
    //Interrupts ved Rising & Falling:
	EICRA = 0b00000100;
}

void X10_Modtager::initX10_modtager(int rx_pin)
{
    //Definer RX input pin.
    rx_pin_ = (rx_pin == 0 || rx_pin == 19 || rx_pin == 15 ? rx_pin : 19);

    pinMode(rx_pin_, INPUT);
}

void X10_Modtager::readingWait()
{
    TCNT2 = 256 - 125; //Vent 0.5 ms
    TCCR2A = 0b0;
    TCCR2B = 0b00000110;

    while ((TIFR2 & (1<<0)) == 0)
    {
        //Vent til overflow
    }
    
    //Sluk clocken:
    TCCR2B = 0b0;
    //Reset overflow:
    TIFR2 = 0b00000001;
}


bool X10_Modtager::checkStartCode()
{
    uint8_t startcode = 0b00001110;
  
    while (digitalRead(rx_pin_) != HIGH)
    {
        /* code */
    }
    
    countOneZeroCross();
    readingWait();
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
    readingWait();
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
    readingWait();
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


bool X10_Modtager::checkSuffix(int Suffix) //1 for unit & 2 for funktion.
{
    uint8_t final_suffix = suffix_Array[Suffix-1];
    
    countOneZeroCross();
    readingWait();
    rollingByteSuffix_ <<= 1;

    if (digitalRead(rx_pin_) == HIGH)
    {
        rollingByteSuffix_++;
    }
    
    rollingByteSuffix_ &= 0b00000011;

    if (rollingByteSuffix_ == final_suffix)
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

     if (rollingByteSuffix_ == 0b0001)
    {
        /* code */
    }
    else if (checkSuffix(1) == true)
    {
        Serial.print("\nUnit Suffix godkendt\n");
        return_array[0] = unit_temp;
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

     if (rollingByteSuffix_ == 0b0010)
    {
        /* code */
    }
    else if (checkSuffix(2) == true)
    {
        Serial.print("\nFunction Suffix godkendt\n");
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
    rollingByteFunction_ = 0;
    rollingByteSuffix_ = 0;
}


void X10_Modtager::countOneZeroCross()
{

    while (zero_detected_modtager != 1)
    {
            //Lav ingenting & Vent til vi får et rising eller falling.
    }

    //Nulstiller Zero_detected:
    zero_detected_modtager = 0;

}

ISR(INT1_vect)
{
    //Sæt interruptet, så vi ved der har været et zerocross.
    zero_detected_modtager = 1;
}
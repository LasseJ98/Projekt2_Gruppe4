#include "X10_Modtager.h"


#define HIGH 0x1
#define LOW  0x0



volatile int zero_detected_modtager = 0;
volatile int last_function = 0;
volatile uint8_t function_temp = 0;
volatile bool function = false;

void X10_Modtager::initZeroCrossInterrupt_Modtager()
{
    //Aktiver interrupts:
    sei();
    //Tænd for Int1:
    EIMSK |= 0b00000010;
    //Interrupts ved Rising & Falling:
	EICRA = 0b00000100;
}

void X10_Modtager::initX10_modtager(int rx_pin, int unit)
{
    //Definer RX input pin.
    rx_pin_ = (rx_pin == 0 || rx_pin == 19 || rx_pin == 15 ? rx_pin : 19);
    unit_ = (unit >= 1 && unit <= 6 ? unit : 1);
        
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
    uint8_t unitCode = unit_Array[unit_-1];
    
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
    countOneZeroCross();
    readingWait();

    if (last_function == 0)
    {
        //Kig efter funktionen ON
        function_temp = function_Array[0];
    }
    else if (last_function == 1)
    {
        //Kig efter funktionen OFF
        function_temp = function_Array[1];
    }
    
    rollingByteFunction_ <<= 1;

    if (digitalRead(rx_pin_) == HIGH)
    {
        rollingByteFunction_++;
    }

    if (rollingByteFunction_ == function_temp)
    {
        return true;
    }

   return false;
}

int* X10_Modtager::receiveCommands()
{
    int8_t unit_temp = unit_Array[unit_-1];
    static int return_array[2];


    if (rollingByteStart_ == 0b1110)
    {
        //Kontrollere om vi allerede har læst startkoden.
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
        //Kontrollere om vi allerede har læst unit_temp.
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
        //Kontrollere om vi allerede har læst Suffixet for Unit
    }
    else if (checkSuffix(1) == true)
    {
        Serial.print("\nUnit Suffix godkendt\n");
        return_array[0] = unit_temp;
        rollingByteSuffix_ = 0;
    }
    else
    {
        return 0;
    }

    if (function == true)
    {
        //Kontrollere om vi allerede har læst function_temp.
    }
    else if (checkFunction() == true)
    {
        Serial.print("\nFunction godkendt\n");
        function = true;
    }
    else
    {
        return 0;
    }

     if (rollingByteSuffix_ == 0b0010)
    {
        //Kontrollere om vi allerede har læst functions suffix.
    }
    else if (checkSuffix(2) == true)
    {
        Serial.print("\nFunction Suffix godkendt\n");

        //Indsætter vores Function i retunering arrayet:
        return_array[1] = rollingByteFunction_;

        //Opdatering af last_function:
        if (last_function == 1)
        {
            last_function = 0;
        }
        else
        {
            last_function = 1;
        } 

        //Resetter så vi er klar til at få nye bits.
        function_temp = 0; 
        rollingByteSuffix_ = 0;
        rollingByteStart_ = 0;
        rollingByteHouse_ = 0;
        rollingByteUnit_ = 0;
        rollingByteFunction_ = 0;
        rollingByteSuffix_ = 0;
        function = false;

        //Retunere arrayet.
        return return_array;
    }
    else
    {
        return 0;
    }
}


void X10_Modtager::countOneZeroCross()
{

    while (zero_detected_modtager != 1)
    {
            //Lav ingenting & Vent til vi får et rising eller falling.
    }

    //Vent lidt yderligere:
    readingWait();

    //Nulstiller Zero_detected:
    zero_detected_modtager = 0;

}

ISR(INT1_vect)
{
    //Sæt interruptet, så vi ved der har været et zerocross.
    zero_detected_modtager = 1;

    
}
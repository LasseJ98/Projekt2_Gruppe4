#include "X10_Sender.h"

#define HIGH 0x1
#define LOW  0x0
#define BIT_DELAY 6.108
#define BIT_LENGTH 1	
#define Overflow_time 10


#define UNIT1 0b01100
#define UNIT2 0b11100
#define UNIT3 0b00100
#define UNIT4 0b10100
#define UNIT5 0b00010

#define ON 0b00101
#define OFF 0b00111

volatile int zero_detected_sender = 0;


void X10_Sender::burstTimerStart()
{
    TCNT2 = 256-250; //Vent 1 ms.
    TCCR2A = 0b00000000;
    TCCR2B = 0b00000100;

    
    while ((TIFR2 & (1<<0)) == 0)
    {
        //Venter på overflow
    }

    //Sluk clocken:
    TCCR2B = 0b00000000;
    //Reset Overflow:
    TIFR2 = 0b00000001;

}

void X10_Sender::initZeroCrossInterrupt_Sender()
{
    sei();
    EIMSK |= 0b00000001;
	EICRA = 0b00000001;
}


//unsigned long first_zerocross;
//unsigned long second_zerocross;

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
    for (size_t i = 0; i < count; i++)
    {
        countOneZeroCross();
    }
    
}

void X10_Sender::countOneZeroCross()
{
    while (zero_detected_sender != 1)
    {
            //Lav ingenting.
    }

    //Nulstiller Zero_detected:
    zero_detected_sender = 0;
}

void X10_Sender::sendStartCode()
{
    byte startcode = 0b1110;
    int bit_size = 4;


   //countOneZeroCross(); //Vent til zerocross med at sende, for at synkronisere.

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = startcode & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.
        digitalWrite(burst_pin_, finalBit); //Burst et 1-tal
      
        burstTimerStart();

        digitalWrite(burst_pin_, LOW); //Sluk for burst
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countOneZeroCross();
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

        

        //delayMicroseconds(BIT_LENGTH); //Vent 950 us.
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
        
       

        digitalWrite(burst_pin_, LOW); //Sluk for burst
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countZeroCross(1); //Vent 1 zero-cross.
    } 
}

ISR(INT0_vect)
{
    zero_detected_sender = 1;
}


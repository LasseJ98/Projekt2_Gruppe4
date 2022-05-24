#include "X10_Sender.h"

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


void X10_Sender::waitTime(int hour, int minutes)
{
    int longTime = hour * (60 * 60)/4;
    int shortTime = (minutes * 60)/4;
    int time = longTime + shortTime;

    for (size_t i = 0; i < time; i++)
    {  
        TCNT1 = 65536-(4*15625); //Et sekund tager 15625 trin, venter 4 sekunder

        TCCR1A = 0b00000000;
        TCCR1B = 0b00000101; //Prescalar på 1024

        while ((TIFR1 & (1<<0)) == 0)
        {
         //Venter på overflow
        }

        //Sluk clocken:
        TCCR1B = 0b00000000;
        //Reset Overflow:
        TIFR1 = 0b00000001;
    }

}

void X10_Sender::initZeroCrossInterrupt_Sender()
{
    sei();
    EIMSK |= 0b00000001;
	EICRA = 0b00000001;
}


void X10_Sender::initX10(int tx_pin)
{
    tx_pin_ = tx_pin;
    
   pinMode(tx_pin_, OUTPUT);

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

    zero_detected_sender = 0; //Ignorer tidligere zerocross
    countOneZeroCross();

   //countOneZeroCross(); //Vent til zerocross med at sende, for at synkronisere.

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = startcode & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.
    
        burstTimerStart();

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
    sendSuffix(1);
    //Vent 6 zerocrosses:
    for (size_t i = 0; i < 6; i++)
    {
        countOneZeroCross();
    }
    

    //Første sending af Command:
    sendStartCode();
    sendHouseA();
    sendFunction(Function);
    sendSuffix(2);
    //Vent 6 zerocrosses:
    for (size_t i = 0; i < 6; i++)
    {
        countOneZeroCross();
    }
}

void X10_Sender::sendHouseA()
{
    byte HouseA = 0b01101001;
    int bit_size = 8;
    

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = HouseA & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.

        burstTimerStart();

        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countOneZeroCross(); //Vent 1 zero-cross.
    }
}

void X10_Sender::sendUnit(int unit)
{
    byte array_Var = unit_Array[unit-1];
    int bit_size = 8;
 
    
   for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = array_Var & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.

        burstTimerStart();
    
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countOneZeroCross(); //Vent 1 zero-cross.
    }
    
}

void X10_Sender::sendFunction(int function)
{
    byte array_Var = function_Array[function-1];
    int bit_size = 8;

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = array_Var & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit.

        burstTimerStart();
        
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countOneZeroCross(); //Vent 1 zero-cross.
    }
}

void X10_Sender::sendSuffix(int Suffix)
{
    byte suffix = suffix_Array[suffix-1];
    int bit_size = 2; //Size of the Suffix

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = suffix & (1 << (bit_size-i));

        digitalWrite(tx_pin_, finalBit); //Send vores bit

        burstTimerStart(); //Burst i 1 ms.
   
        digitalWrite(tx_pin_, LOW); //Sætter TX low.
        countOneZeroCross(); //Vent 1 zero-cross.
    }
}



void X10_Sender::sendMorningRoutine()
{
    if (morningDevice1 > 0 && morningFunction1 > 0)
    {
        sendCommand(morningDevice1, morningFunction1);
    }
    if (morningDevice2 > 0 && morningFunction2 > 0)
    {
        sendCommand(morningDevice2, morningFunction2);
    }
    if (morningDevice3 > 0 && morningFunction3 > 0)
    {
        sendCommand(morningDevice3, morningFunction3);
    }
    if (morningDevice4 > 0 && morningFunction4 > 0)
    {
        sendCommand(morningDevice4, morningFunction4);
    }
    if (morningDevice5 > 0 && morningFunction5 > 0)
    {
        sendCommand(morningDevice5, morningFunction5);
    }
    if (morningDevice6 > 0 && morningFunction6 > 0)
    {
        sendCommand(morningDevice6, morningFunction6);
    }
}

void X10_Sender::configMorning(int unit1, int function1, int unit2, int function2, int unit3, int function3, int unit4, int function4, int unit5, int function5, int unit6, int function6)
{
    morningDevice1 = unit1;
    morningDevice2 = unit2;
    morningDevice3 = unit3;
    morningDevice4 = unit4;
    morningDevice5 = unit5;
    morningDevice6 = unit6;

    morningFunction1 = function1;
    morningFunction2 = function2;
    morningFunction3 = function3;
    morningFunction4 = function4;
    morningFunction5 = function5;
    morningFunction6 = function6;
}


void X10_Sender::sendEveningRoutine()
{
    if (eveningDevice1 > 0 && eveningFunction1 > 0)
    {
        sendCommand(eveningDevice1, eveningFunction1);
    }
    if (eveningDevice2 > 0 && eveningFunction2 > 0)
    {
        sendCommand(eveningDevice2, eveningFunction2);
    }
    if (eveningDevice3 > 0 && eveningFunction3 > 0)
    {
        sendCommand(eveningDevice3, eveningFunction3);
    }
    if (eveningDevice4 > 0 && eveningFunction4 > 0)
    {
        sendCommand(eveningDevice4, eveningFunction4);
    }
    if (eveningDevice5 > 0 && eveningFunction5 > 0)
    {
        sendCommand(eveningDevice5, eveningFunction5);
    }
    if (eveningDevice6 > 0 && eveningFunction6 > 0)
    {
        sendCommand(eveningDevice6, eveningFunction6);
    }
}


void X10_Sender::configEveningRoutine(int unit1, int function1, int unit2, int function2, int unit3, int function3, int unit4, int function4, int unit5, int function5, int unit6, int function6)
{
    eveningDevice1 = unit1;
    eveningDevice2 = unit2;
    eveningDevice3 = unit3;
    eveningDevice4 = unit4;
    eveningDevice5 = unit5;
    eveningDevice6 = unit6;

    eveningFunction1 = function1;
    eveningFunction2 = function2;
    eveningFunction3 = function3;
    eveningFunction4 = function4;
    eveningFunction5 = function5;
    eveningFunction6 = function6;
}


ISR(INT0_vect)
{
    zero_detected_sender = 1;
}




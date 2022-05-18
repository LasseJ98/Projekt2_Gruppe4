#include <Arduino.h>

/*void setup() 
{
 pinMode(1,OUTPUT);
 pinMode(LED_BUILTIN,OUTPUT);
}

void loop() 
{
    byte startcode = 0b1110;
    int bit_size = 4;
    digitalWrite(LED_BUILTIN,HIGH);

    for (size_t i = 1; i <= bit_size; i++)
    {
       byte finalBit = startcode & (1 << (bit_size-i));

        digitalWrite(1, finalBit); //Send vores bit.
        delayMicroseconds(950); //Vent 950 us.
        digitalWrite(1, LOW); //Sætter TX low.
        delayMicroseconds(8000); //Vent 950 us.
    }
    digitalWrite(LED_BUILTIN,LOW);
    delay(5000);
}*/

//Modtager:

/*void setup() 
{
 pinMode(0,INPUT);
 pinMode(LED_BUILTIN,OUTPUT);
}

void loop() 
{
    digitalWrite(LED_BUILTIN,LOW);
    byte startcode = 0b1110;
    byte readingBit = 0b0000;

    while (digitalRead(0) != 0)
    {
       for (size_t i = 1; i <= 4; i++)
       {
           readingBit |= (digitalRead(0) << i); 
           delayMicroseconds(950);
           delayMicroseconds(8000);
           if (readingBit == startcode)
           {
               digitalWrite(LED_BUILTIN,HIGH);
               delay(1000);
               digitalWrite(LED_BUILTIN,LOW);
           } 
       }
    }
}*/





    
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "arduinoUART.h"

void setup()
{
  InitUART(9600, 8, 1);
  sei();
  //pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(8, INPUT);
  // initialize control over the keyboard:
  //Serial.print("Programmet er startet");
  //Serial.print("\n\r");
}

void loop()
{
  // Tom main
}

 ISR(USART0_RX_vect) // Implementering af interrupt
 {
   if (CharReady() == 1) // Tjek for indkommende seriel data
   {
     char inChar = ReadChar(); // Læs indkommende seriel data

     switch (inChar) // here skal alle ændringerne baseret på UART ske. aka global variables, etc...
     {
     case 1:
       //digitalWrite(7, HIGH);
       break;

     case 2:
       //digitalWrite(6, HIGH);

       break;

     case 3:

       break;

     case 4:

       break;

     case 5:

       break;

     case 6:

       break;

     case 7:

       break;

     case 8:

       break;

     }
   }
 }
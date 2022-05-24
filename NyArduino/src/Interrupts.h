#include <Arduino.h>
#include <avr/interrupt.h>

void activate()
{
    sie();
    interrupts();
    attachInterrupt(digitalPintoInterrupt(3),PS_ISR,CHANGE);
}

ISR(PS_ISR,ISR_NOBLOCK)
{
  int PS = digitalRead(3);

  Serial.write(PS);
}

ISR(USART0_RX_vect) // 256 mulig inputs fra 1 byte.
{

 if (Serial.available() > 0) // Tjek for indkommende seriel data
  {
    char inChar = Serial.read(); // Læs indkommende seriel data
    
    switch(inChar) // here skal alle ændringerne baseret på UART ske. aka global variables, etc...

    case '1' :
    
    digitalWrite(7, HIGH); 
    break;
    
    case 1 :

    digitalWrite(6, HIGH); 

    break;

    case 3 :

    break;
    
    case 4 :

    break;

    case 5 :

    break;

    case 6 :

    break;
    
    case 7 :

    break;

    case 8 :

    break;

    case 9 :

    break;
    
    case 10 :

    break;

    case 11 :

    break;

    case 12 :

    break;
    
    case 13 :

    break;

    case 14 :

    break;

    case 15 :

    break;

    case 16 :

    break;

    case 17 :

    break;

    case 18 : 

    break;
  
    default:
    
    break;
  }

}
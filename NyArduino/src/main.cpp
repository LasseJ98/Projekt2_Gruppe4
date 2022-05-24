#include <Arduino.h>
#include <avr\interrupt.h>

void activate();
void PS();

void setup()
{
  // open the serial port:
  Serial.begin(9600);
  activate();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(8, INPUT);
  // initialize control over the keyboard:
  Serial.print("Programmet er startet");
  Serial.print("\n\r");
}

void loop()
{
  //bool AdminAdgang = digitalRead(8); // Aflæs fra DE2 boardet hvis systemet skal være låst op eller ej
 // if (AdminAdgang == true) // Hvis der er låst op for adming adgang
 // {
 // if (Serial.available() > 0) // Tjek for indkommende seriel data
  //{
  //  char inChar = Serial.read(); // Læs indkommende seriel data
 //   Serial.println(inChar); // Udskriv hvad brugeren indtaster

 //   if (inChar == '1')
 //   {
  //    digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at konfigurere morgenrutine
    //}
    //else if (inChar == '2')
   // {
  //    digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at konfigurere aftenrutine

  //  }
 //   else if (inChar == '3')
//    {
//      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at afbryde admin adgang
//    }
//     else
//     {
//       Serial.print("Du har ikke valgt en gyldig valgmulighed");
//     }

//     if (inChar == '1') // Når enheden er låst for admin adgang. Manuelt styring
//     {
//       digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at styre lys
//     }
//     else if (inChar == '2')
//     {
//       digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at styre lyd
//     }
//     else if (inChar == '3')
//     {
//       digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at styre dørlås
//     }
//     else if (inChar == '4')
//     {
//       digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at styre gardiner
//     }
//     else if (inChar == '5')
//     {
//       digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at styre TV
//     }
//     else if (inChar == '6')
//     {
//       digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode for at styre vandbeholder
//     }
//     else
//     {
//       Serial.print("Du har ikke valgt en gyldig valgmulighed");
//     }
//   }
//   }
 }

void PS()
{
  int PS = digitalRead(3);

  Serial.write(PS);
}

void activate()
{
    interrupts();
    attachInterrupt(digitalPinToInterrupt(3),PS,CHANGE);
}

ISR(USART0_RX_vect) // 256 mulig inputs fra 1 byte.
{

 if (Serial.available() > 0) // Tjek for indkommende seriel data
  {
    char inChar = Serial.read(); // Læs indkommende seriel data
    
    switch(inChar) // here skal alle ændringerne baseret på UART ske. aka global variables, etc...
  {
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
}
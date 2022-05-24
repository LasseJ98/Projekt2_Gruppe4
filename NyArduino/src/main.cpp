#include "Interrupts"

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

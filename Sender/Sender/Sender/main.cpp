#include <Arduino.h>

void setup()
{
  // open the serial port:
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  // initialize control over the keyboard:
  Serial.print("Programmet er startet");
  Serial.print("\n\r");
  char inChar;
}

void loop()
{
  // check for incoming serial data:
  if (Serial.available() > 0)
  {
    // read incoming serial data:
    char inChar = Serial.read();
    // Type the next ASCII value from what you received:
    Serial.println(inChar);
    // while () voltage on pin == high, sendchar(1) or something. Når systemet er låst op for admin adgang
    if (inChar == '1')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '2')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '3')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '4')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else
    {
      Serial.print("Du har ikke valgt en gyldig valgmulighed");
    }

    // Når enheden er låst for admin adgang
    if (inChar == '1')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '2')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '3')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '4')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '5')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '6')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '7')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else if (inChar == '8')
    {
      digitalWrite(LED_BUILTIN, HIGH); // Skal erstattes med kode fra sender og modtager
    }
    else
    {
      Serial.print("Du har ikke valgt en gyldig valgmulighed");
    }
  }
}

// void loop()
// {
//     // check for incoming serial data:
//     if (Serial.available() > 0)
//     {
//         // read incoming serial data:
//         char inChar = Serial.read();
//         // Type the next ASCII value from what you received:
//         Serial.println(inChar);

//         if (inChar == 'h')
//         {
//             digitalWrite(LED_BUILTIN, HIGH);
//         }
//     }
// }
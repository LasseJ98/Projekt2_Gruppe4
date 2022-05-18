#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include "uart_int.h"
#include "led.h"
#include "LM75.h"

ISR(USART0_RX_vect)
{
  char modtaget_tegn;

  // Aflæs UART modtage-register
  modtaget_tegn = UDR0;
  // Reager kun på lovlige tegn
  if ((modtaget_tegn >= '0') && (modtaget_tegn <= '7'))
  {
    // Toggle aktuelle lysdiode
    toggleLED(modtaget_tegn - '0');
    // Send streng "LED nummer x er toggled"
	SendString("LED nummer ");
    SendChar(modtaget_tegn);
    SendString(" er toggled\r\n");
  }
}  
 
int main()
{
  int temp;

  // Initier UART (med RX interrupt enable)
  InitUART(9600, 8, 1);
  // Global interrupt enable
  sei();
  // Initier LED port
  initLEDport();
  // Initier temperatur sensor
  LM75_init();
  while (1)
  {
    // Aflæs temperaturen (OBS: Enhed = halve grader)
	temp = LM75_temperature(0);
	// Vis i formatet "26,5 grader" (og linieskift)
    SendInteger(temp/2);
	SendChar(',');
    if (temp & 0b00000001)
      SendChar('5');
    else
      SendChar('0');
    SendString(" grader\r");
	// Vent 1 sekund
    _delay_ms(1000);
  }
}
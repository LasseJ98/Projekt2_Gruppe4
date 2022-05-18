/*
 * LAB12_2_RX3.c
 *
 * Created: 26-11-2020 16:00:52
 * Author : sebas
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"
#include "sw_uart.h"

#define BAUD_RATE 9600

int main(void)
{
	initLEDport();
	initSWUART(BAUD_RATE);
	sei();
	while (1)
	{
 		SendString("Software UART test\r\n");
		unsigned char c = 0;
		while (c != 'Q')
		{
 			SendString("Send et tegn\r\n");
 			SendString("Q for at afslutte...\r\n");
			c = ReadChar();
			writeAllLEDs(c);
			SendString("ASCII: ");
			SendInteger(c);
			SendChar('\r');
			SendChar('\n');
			
			SendCharBinary(c);
			SendChar('\r');
			SendChar('\n');

			SendChar(c);
 			SendString(" + 1 giver: ");
			SendChar(c+1);
			SendString("\r\n\r\n");
		}
 		SendString("Farvel!\r\n");
		while (1) {}
	}
}


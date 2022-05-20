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
	SendString("Uart is working\r\n");
	unsigned char input = 0;
    unsigned char password = 0;
	while (1)
	{
        // while () voltage on pin == high, sendchar(1) or something
			input = ReadChar();
            
            switch(input)
            {
                case '1':
                writeAllLEDs(input); // replace with sender til modtager stuff
                break;
                case '2':
                writeAllLEDs(input); // replace with sender til modtager stuff
                break;
                case '3':
                writeAllLEDs(input); // replace with sender til modtager stuff
                break;
                case '4':
                writeAllLEDs(input); // replace with sender til modtager stuff
                break;
            }
	}
    
}
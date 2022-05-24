#include <avr/io.h>
#include <stdlib.h>
#include "arduinoUART.h"

// Target CPU frequency
#define XTAL 16000000

/*************************************************************************
UART 0 initialization:
    Asynchronous mode.
    Baud rate = 9600.
    Data bits = 8.
    RX and TX enabled.
    No interrupts enabled.
    Number of Stop Bits = 1.
    No Parity.
    Baud rate = 9600.
    Data bits = 8.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char Rx_Int)
{
    if (BaudRate < 300 || BaudRate > 115200 || DataBit < 5 || DataBit > 8)
    {
        return;
    }
    //	UBRR0 = 103;  // 16000000 / (16*9600) - 1 = 103,16  (9600 baud)
    UBRR0 = 1000000 / BaudRate - 1; // 16000000 / (16*9600) - 1 = 103,16  (9600 baud)
    int interruptBits = (Rx_Int != 0) ? (1 << 2) : 0;
    ;
    int RX_enable = 1 << 4;
    int TX_enable = 1 << 3;
    //	UCSR0B = 0b00011000;  // no interrupts, RX enable, TX enable
    UCSR0B = (interruptBits << 5) + RX_enable + TX_enable;

    int mode = 0b00 << 6;       // asynchronous mode
    int parity = 0b00 << 4;     // no parity: 0b00, even parity: 0b10, odd parity: 0b11
    int stopBitMode = 0b0 << 3; // 1 stop bit: 0b0, 2 stop bits: 0b1;
                                //	UCSR0C = 0b00000110;
    UCSR0C = mode + parity + stopBitMode + ((DataBit - 5) << 1);
    UCSR0A = 0; // clear flags
}

/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
    //   return UCSR0A & 0b10000000;
    return UCSR0A & (1 << 7); // nemmere at læse og se om 1-tallet står på den rigtige plads
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
    while (!CharReady())
    {
    }

    return UDR0;
}

void SendChar(char Tegn)
{
    //	while ((UCSR0A & 0b00100000) == 0)  // wait for UDR0 to be ready for a new byte
    while ((UCSR0A & (1 << 5)) == 0) // wait for UDR0 to be ready for a new byte
    {
    }

    UDR0 = Tegn;
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
   Streng: Pointer to the string.
*************************************************************************/
void SendString(char *Streng)
{
    for (int i = 0; Streng[i] != 0; i++)
    {
        SendChar(Streng[i]);
    }
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
    Tal: The integer to be converted and sent.
*************************************************************************/
void SendInteger(int Tal)
{
    char streng[10];
    itoa(Tal, streng, 10);
    SendString(streng);
}

/************************************************************************/
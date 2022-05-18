/*
 * sw_uart.c
 *
 * Created: 26-11-2020 17:35:08
 *  Author: sebas
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "led.h"
#include "sw_uart.h"

#define XTAL 16000000

// deklaration for funktioner og variable der bruges internt, og som ikke skal tilgås fra kode uden for denne fil:

void enablePinChangeInterrupt1();
void disablePinChangeInterrupt1();
void startRXTimer(unsigned int cycles);
void stopRXTimer();
void setRXTimerDelay(unsigned int cycles);
void startTXTimer(unsigned int cycles);
void stopTXTimer();
void sendBit(unsigned char bit);

unsigned char volatile receiveShiftRegister = 0;  // midlertidigt lager for modtagede bits indtil der er nok til at fylde swUDR
unsigned char volatile bitsReceived = 0;  // hvor mange bits der er modtaget i receiveShiftRegister
unsigned char volatile swUDRin;  // den senest modtagede værdi
unsigned char volatile swRXCnFlag = 0;  // fortæller om der er modtaget nye data i UDRn siden den sidst blev læst

unsigned char volatile sendShiftRegister = 0;  // midlertidigt lager for bits der skal sendes
unsigned char volatile bitsSent = 0;  // hvor mange bits der er modtaget i receiveShiftRegister
unsigned char volatile swUDREn = 1;  // fortæller om UART'en er klar til at sende en ny værdi

unsigned int startBitDelay = 2500;  // antal cycles der skal ventes ved en BAUD rate på 9600 og en CPU-frekvens på 16 MHz
unsigned int bitDelay = 1667;  // antal cycles der skal ventes ved en BAUD rate på 9600 og en CPU-frekvens på 16 MHz

void initSWUART(unsigned long baudRate)
{
	if (baudRate < 300 || baudRate > 115200)
	return;
	
	startBitDelay = (long) XTAL * 3 / 2 / baudRate;
	bitDelay = (long) XTAL / baudRate;
	
	UCSR0B = 0;  // sluk for UART'en
	PORTE = 0b00000011;  // sørg for at udgangen er høj fra starten
	DDRE = 0b00000010;    // gør benene på PE til input (særligt ben 0, som er RXD0), bortset fra ben 1, som er TXD0
	enablePinChangeInterrupt1();
}

void enablePinChangeInterrupt1()
{
	PCMSK1 = 1;  // slå PCINT8 til og PCINT9..PCINT15 fra, så ingen andre ben kan udløse vores ISR
	PCICR = 0b00000010; // slå interrupt PCI1 til
}

void disablePinChangeInterrupt1()
{
	PCMSK1 = 0;  // slå PCINT8..PCINT15 fra, så ingen ben kan udløse vores ISR
	PCICR = 0; // slå interrupt PCI1 fra
}

void startRXTimer(unsigned int cycles)
{
	TCCR1A = 0;  // Normal mode, bruger ingen pins
	OCR1A = cycles;
	TCCR1B = 0b00001001;  // timer slået til, ingen pre-scaling, CTC
	TIMSK1 = 0b00000010;  // slå interrupt på timer 1 til ved output compare A match
}

void stopRXTimer()
{
	TIMSK1 = 0;  // slå alle interrupts fra timer 1 fra
	TCCR1B = 0;  // timer 1 slået fra
}

void setRXTimerDelay(unsigned int cycles)
{
	OCR1A = cycles;
}

void startTXTimer(unsigned int cycles)
{
	TCCR3A = 0;  // Normal mode, bruger ingen pins
	OCR3A = cycles;
	TCCR3B = 0b00001001;  // timer slået til, ingen pre-scaling, CTC
	TIMSK3 = 0b00000010;  // slå interrupt på timer 3 til ved output compare A match	
}

void stopTXTimer()
{
	TIMSK3 = 0;  // slå alle interrupts fra timer 3 fra
	TCCR3B = 0;  // timer 3 slået fra	
}


ISR(PCINT1_vect)  // start-bit modtaget
{
	disablePinChangeInterrupt1();  // slå interruptet fra, så det ikke bliver udløst, hver gang en ny bit bliver sendt
	bitsReceived = 0;
	startRXTimer(startBitDelay);
}

ISR(TIMER1_COMPA_vect)
{
	if (bitsReceived == 0)
		setRXTimerDelay(bitDelay);  // ændr forsinkelse fra startBitDelay til bitDelay, dvs. fra 1,5 periode til 1 periode
	
	bitsReceived++;
	if (bitsReceived <= 8)
	{
		receiveShiftRegister = (receiveShiftRegister >> 1) | ((PINE & 0b00000001) << 7);  // indsæt bit fra indgangen i receiveShiftRegister fra venstre og flyt de andre bits til højre
	}
	else // vi er nået til stop-bitten
	{
		swUDRin = receiveShiftRegister;
		swRXCnFlag = 1;  // vi har modtaget noget nyt i swUDR, der endnu ikke er læst
		stopRXTimer();
		enablePinChangeInterrupt1();
	}
}

void sendBit(unsigned char bit)
{
	if (bit)
	{
		PORTE |= 0b00000010;  // sæt bit 1 i PE (TXD0)
	}
	else
	{
		PORTE &= 0b11111101;  // ryd bit 1 i PE (TXD0)
	}
}

ISR(TIMER3_COMPA_vect)
{
	if (bitsSent == 0)
	{
		sendBit(0);  // send start-bit
	}
	else if (bitsSent < 9)  // start-bit sendt, mindre end 8 data-bits sendt
	{
		sendBit(sendShiftRegister & 1);  // send LSB fra sendShiftRegister
		sendShiftRegister = sendShiftRegister >> 1;
	}
	else if (bitsSent == 9)
	{
		sendBit(1);  // send end-bit og kør én gang til
	}
	else
	{
		stopTXTimer();  // nu har vi sendt 1 start-bit, 8 data-bits, 1 end-bit OG ventet en periode mere
		swUDREn = 1;  // klar til at modtage et nyt tegn
	}
	bitsSent++;
}

unsigned char CharReady()
{
	return swRXCnFlag;
}

char ReadChar()
{
  	while (swRXCnFlag == 0)
 	{}
	swRXCnFlag = 0;
	return swUDRin;
}


void SendChar(char Tegn)
{
	while (swUDREn == 0)  // vent på at der er fri bane til at sende
	{}
	swUDREn = 0;  // sørg for at der ikke påbegyndes afsending af et nyt tegn, mens vi sender dette
	bitsSent = 0;
	sendShiftRegister = Tegn;
	startTXTimer(bitDelay);
}

void SendString(char* Streng)
{
	for (int i = 0; Streng[i] != 0; i++)
	{
		SendChar(Streng[i]);
	}
}

void SendInteger(int Tal)
{
	char streng[10];
	itoa(Tal, streng, 10);
	SendString(streng);
}

void SendCharBinary(char c)
{
	char streng[10];
	itoa(c, streng, 2);
	SendString(streng);
}
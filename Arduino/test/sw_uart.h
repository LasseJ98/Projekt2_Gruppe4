/*
 * sw_uart.h
 *
 * Created: 26-11-2020 17:35:19
 *  Author: sebas
 */ 


#ifndef SW_UART_H_
#define SW_UART_H_


void initSWUART(unsigned long baudRate);

unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);
void SendCharBinary(char c);

#endif /* SW_UART_H_ */
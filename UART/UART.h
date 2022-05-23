#ifndef __SERIAL_H__
#define __SERIAL_H__
#pragma once

#include <Windows.h>
#include <memory.h>

#define FC_DTRDSR 0x01
#define FC_RTSCTS 0x02
#define FC_XONXOFF 0x04
#define ASCII_BEL 0x07
#define ASCII_BS 0x08
#define ASCII_LF 0x0A
#define ASCII_CR 0x0D
#define ASCII_XON 0x11
#define ASCII_XOFF 0x13

class UART
{
    friend void styrManuelt(char input);
    friend void adminUI(char input);

public:
    UART();
    ~UART();

    bool Open(int nPort = 2, int nBaud = 9600);
    bool Close(void);

    int ReadData(void*, int);
    int SendData(const char*, int);
    int ReadDataWaiting(void);
    void SendTest(int port, int baudRate);
    bool IsOpened(void) { return (m_bOpened); }
    void printUI();
    void printStyrManueltUI();
    void UIinput(char input);

    void styrManuelt(char input);

protected:
    bool WriteCommByte(unsigned char);

    HANDLE m_hIDComDev;
    OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
    bool m_bOpened;
};

#endif

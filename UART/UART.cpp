#include "UART.h"
#include <iostream>
#include <conio.h>

using namespace std;

// Globale variable til switch
char input;
int password;

UART::UART()
{

    memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
    memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));
    m_hIDComDev = NULL;
    m_bOpened = false;
}

UART::~UART()
{

    Close();
}

bool UART::Open(int nPort, int nBaud)
{

    if (m_bOpened)
        return (TRUE);

    wchar_t szPort[15];
    wchar_t szComParams[50];
    DCB dcb;

    wsprintf(szPort, L"COM%d", nPort);
    m_hIDComDev = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
    if (m_hIDComDev == NULL)
        return (FALSE);

    memset(&m_OverlappedRead, 0, sizeof(OVERLAPPED));
    memset(&m_OverlappedWrite, 0, sizeof(OVERLAPPED));

    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
    CommTimeOuts.ReadTotalTimeoutConstant = 0;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant = 5000;
    SetCommTimeouts(m_hIDComDev, &CommTimeOuts);

    wsprintf(szComParams, L"COM%d:%d,n,8,1", nPort, nBaud);

    m_OverlappedRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    m_OverlappedWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    dcb.DCBlength = sizeof(DCB);
    GetCommState(m_hIDComDev, &dcb);
    dcb.BaudRate = nBaud;
    dcb.ByteSize = 8;
    unsigned char ucSet;
    ucSet = (unsigned char)((FC_RTSCTS & FC_DTRDSR) != 0);
    ucSet = (unsigned char)((FC_RTSCTS & FC_RTSCTS) != 0);
    ucSet = (unsigned char)((FC_RTSCTS & FC_XONXOFF) != 0);
    if (!SetCommState(m_hIDComDev, &dcb) ||
        !SetupComm(m_hIDComDev, 10000, 10000) ||
        m_OverlappedRead.hEvent == NULL ||
        m_OverlappedWrite.hEvent == NULL)
    {
        DWORD dwError = GetLastError();
        if (m_OverlappedRead.hEvent != NULL)
            CloseHandle(m_OverlappedRead.hEvent);
        if (m_OverlappedWrite.hEvent != NULL)
            CloseHandle(m_OverlappedWrite.hEvent);
        CloseHandle(m_hIDComDev);
        return (FALSE);
    }

    m_bOpened = TRUE;

    return (m_bOpened);
}

bool UART::Close(void)
{

    if (!m_bOpened || m_hIDComDev == NULL)
        return (TRUE);

    if (m_OverlappedRead.hEvent != NULL)
        CloseHandle(m_OverlappedRead.hEvent);
    if (m_OverlappedWrite.hEvent != NULL)
        CloseHandle(m_OverlappedWrite.hEvent);
    CloseHandle(m_hIDComDev);
    m_bOpened = FALSE;
    m_hIDComDev = NULL;

    return (TRUE);
}

int UART::SendData(const char* buffer, int size)
{
    if (!m_bOpened || m_hIDComDev == NULL)
        return (0);

    DWORD dwBytesWritten = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        WriteCommByte(buffer[i]);
        dwBytesWritten++;
    }

    return ((int)dwBytesWritten);
}

bool UART::WriteCommByte(unsigned char ucByte)
{
    bool bWriteStat;
    DWORD dwBytesWritten;

    bWriteStat = WriteFile(m_hIDComDev, (LPSTR)&ucByte, 1, &dwBytesWritten, &m_OverlappedWrite);
    if (!bWriteStat && (GetLastError() == ERROR_IO_PENDING))
    {
        if (WaitForSingleObject(m_OverlappedWrite.hEvent, 1000))
            dwBytesWritten = 0;
        else
        {
            GetOverlappedResult(m_hIDComDev, &m_OverlappedWrite, &dwBytesWritten, FALSE);
            m_OverlappedWrite.Offset += dwBytesWritten;
        }
    }

    return (TRUE);
}

void UART::SendTest(int port, int baudRate)
{
    char data[4];

    UART* s = new UART();

    if (!s->Open(port, baudRate))
    {
        cout << "Could not open COM" << port << endl;
    }

    // Sending a string of 4 characters
    data[0] = 0x31;
    data[1] = 0x32;
    data[2] = 0x33;
    data[3] = 0x0D; // ASCII CR
    s->SendData(data, 4);

    s->Close();

    delete s;
}

void UART::printUI()
{
    cout << "Tast 1 for at styre manuelt" << endl;
    cout << "--------------" << endl;
    cout << "Tast 2 for at konfiguerer systemet" << endl;
    cout << "--------------" << endl;
    cout << "Tast 3 for at udskrive menuen" << endl;
    cout << "--------------" << endl;
    cout << "Tast 4 for at annulerer" << endl;
    cout << "--------------" << endl;
}

void UART::printStyrManueltUI()
{
    cout << "Vaelg enheden som skal styres:" << endl;
    cout << "1: Styr lys" << endl;
    cout << "2: Styr lyd" << endl;
    cout << "3: Styr doerlaas" << endl;
    cout << "4: Styr gardiner" << endl;
    cout << "5: Styr TV" << endl;
    cout << "6: Styr vandbeholder" << endl;
    cout << "7: Print valgmuligheder" << endl;
    cout << "8: Afbrud manuelt styring" << endl;
}

void UART::UIinput(char input)
{
    switch (input)
    {
    case '1':
        printStyrManueltUI();

        for (; true;) // Uendelig for-loop
        {
            styrManuelt(*input); // Kald på funktionen til at styre systemet manuelt
        }
        break;

    case '2':
        if (password != 0); // Besked fra arduino om at koden fra DE2 boardet er rigtigt)
        {
            adminUI(input); // Anmod om input fra admin, og derefter udfør kommandoen som er tilknyttet til det valgte tast 
        }
        break;

    case '3':
        printUI(); // Udskriv menuen igen

        break;

    case '4':
        // Ingenting da vi bare skal ud af menuen uden at gøre noget
        break;

    default:
        cout << "Denne tast er ikke en af valgmulighederne" << endl; //Fejlmeddelse
        break;
    }
}

void UART::styrManuelt(char input)
{
    int lysstyrke;
    char* intensitet;
    int controlManual;
    switch (input)
    {
    case '1':
        cout << "Vaelg lysstyrke: " << endl; // Visuel feedback til bruger om at give input
        cout << "1: Sluk lyset" << endl;
        cout << "2: Daempet lys" << endl;
        cout << "3: Straalende lys" << endl;
        cout << "4: Fuld styrke" << endl;
        cin >> lysstyrke; // Anmod brugeren om input for lysstyrke
        if (lysstyrke == 1) // Hvis brugeren vælger 1, så slukkes lyset
        {
            cout << "Du har valgt Sluk lyset" << endl;
            *intensitet = 0;
        }
        else if (lysstyrke == 2) // Hvis brugeren vælger 2, så sættes lysstyrken til 33%
        {
            cout << "Du har valgt Lyset daempes" << endl;
            *intensitet = 33;
        }

        else if (lysstyrke == 3) // Hvis brugeren vælger 3, så sættes lysstyrken til 66%
        {
            cout << "Du har valgt Straalende lys" << endl;
            *intensitet = 66;
        }

        else if (lysstyrke == 4) // Hvis brugeren vælger 4, så tændes lyset til fuld styrke
        {
            cout << "Du har valgt Fuld styrke" << endl;
            *intensitet = 100;
        }

        SendData(intensitet, 1); // Send den nye værdi over til Arduino
        break;

    case '2':
        SendData(&input, 1); // Send det samme som brugeren indtaster over til microcontroller, hvor så at Arduinoen gør noget specifikt ud fra hvad brugeren tastede
        break;

    case '3':
        SendData(&input, 1); // Send det samme som brugeren indtaster over til microcontroller, hvor så at Arduinoen gør noget specifikt ud fra hvad brugeren tastede
        break;

    case '4':
        SendData(&input, 1); // Send det samme som brugeren indtaster over til microcontroller, hvor så at Arduinoen gør noget specifikt ud fra hvad brugeren tastede
        break;

    case '5':
        SendData(&input, 1); // Send det samme som brugeren indtaster over til microcontroller, hvor så at Arduinoen gør noget specifikt ud fra hvad brugeren tastede
        break;

    case '6':
        SendData(&input, 1); // Send det samme som brugeren indtaster over til microcontroller, hvor så at Arduinoen gør noget specifikt ud fra hvad brugeren tastede
        break;

    case '7':
        printStyrManueltUI(); // Udskriv menuen igen 
        break;

    case '8':
        // Ingenting da vi bare skal ud af styr manuelt menuen uden at gøre noget
        break;

    default:
        cout << "Denne tast er ikke en af valgmulighederne" << endl; // Fejlmeddelse
        break;
    }
}

void styrManuelt(char input)
{
}

void adminUI(char input)
{
    char adminInput;
    cout << "Vaelg rutinen som der skal aendres paa" << endl;
    cout << "1: Morgenrutine" << endl;
    cout << "2: Aftenrutine" << endl;
    cin >> adminInput;
    if (adminInput == 1)
    {
        cout << "Du har valgt at konfigurer morgenrutine" << endl;
        styrManuelt(input);
    }
    else if (adminInput == 2)
    {
        cout << "Du har valgt at konfigurer aftenrutine" << endl;
        styrManuelt(input);
    }
    else
    {
        cout << "Du har ikke valgt en gyldig valgmulighed" << endl;
    }
}

int UART::ReadDataWaiting(void)
{

    if (!m_bOpened || m_hIDComDev == NULL)
        return (0);

    DWORD dwErrorFlags;
    COMSTAT ComStat;

    ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);

    return ((int)ComStat.cbInQue);
}

int UART::ReadData(void* buffer, int limit)
{

    if (!m_bOpened || m_hIDComDev == NULL)
        return (0);

    bool bReadStatus;
    DWORD dwBytesRead, dwErrorFlags;
    COMSTAT ComStat;

    ClearCommError(m_hIDComDev, &dwErrorFlags, &ComStat);
    if (!ComStat.cbInQue)
        return (0);

    dwBytesRead = (DWORD)ComStat.cbInQue;
    if (limit < (int)dwBytesRead)
        dwBytesRead = (DWORD)limit;

    bReadStatus = ReadFile(m_hIDComDev, buffer, dwBytesRead, &dwBytesRead, &m_OverlappedRead);
    if (!bReadStatus)
    {
        if (GetLastError() == ERROR_IO_PENDING)
        {
            WaitForSingleObject(m_OverlappedRead.hEvent, 2000);
            return ((int)dwBytesRead);
        }
        return (0);
    }

    return ((int)dwBytesRead);
}

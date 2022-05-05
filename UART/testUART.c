#include "UART.h"

bool sendExample(int port, int baudRate)
{
    char data[4];

    CSerial *s = new CSerial();

    if (!s->Open(port, baudRate))
    {
        std_out << _T("Could not open COM") << port << endl;
        return false;
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

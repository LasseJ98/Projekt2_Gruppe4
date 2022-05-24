#include "UART.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
    UART C1;
    C1.Open(6, 9600); // Åben COM6 til bed en baud rate på 9600
    C1.printUI(); // Udskriv menuen
    int password = 0;
    char i = 0;
    for (; true;) // Uendelig for-loop
    {
        i = 0; // Nulstiller hvad brugeren har skrevet
        i = _getch(); // Hent hvad brugeren taster opå tasteturet
        if (password != 0) // fix ReadData
        {
            cout << "Admin password accepted" << endl;
        }
        if (i != 0) // Tjekker hvis der bliver trykket på en tast, altså en software interrupt. 0 er ASCII værdien for NULL
        {
            cout << i << endl; // Udskriv hvad brugeren taster
            C1.UIinput(i); // Anmod om input fra brugeren, og derefter udfør kommandoen som er tilknyttet til det valgte tast
        }
    }
}

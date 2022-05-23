#include "UART.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
    UART C1;
    C1.Open(6, 9600);
    C1.printUI(); // Udskriv menuen
    int password = 0;
    char i = 0;
    for (; true;) // Uendelig for-loop
    {
        i = 0;
        i = _getch();
        if (password != 0) // fix ReadData
        {
            cout << "Admin password accepted" << endl;
        }
        if (i != 0) // Tjekker hvis der bliver trykket på en tast, altså en software interrupt. 0 er ASCII værdien for NULL
        {
            cout << i << endl;
            C1.UIinput(i); // Anmod om input fra brugeren, og derefter udfør kommandoen som er tilknyttet til det valgte tast
        }
    }
}

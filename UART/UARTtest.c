#include "UART.h"
#include <iostream>
#include <conio.h>
using namespace std;

int main()
{
    UART C1;
    C1.Open();
    C1.printUI();
    for (; true;) // Uendelig for-loop
    {
        if (char i = getch() != 0) // Tjekker hvis der bliver trykket på en tast, altså en software interrupt. 0 er ASCII værdien for NULL
        {
            C1.UIinput(i); // Anmod om input fra brugeren, og derefter udfør kommandoen som er tilknyttet til det valgte tast
        }
    }
}

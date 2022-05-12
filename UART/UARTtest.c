#include "UART.h"
#include <iostream>
using namespace std;

int main()
{
    UART C1;
    C1.Open();
    C1.printUI();
}

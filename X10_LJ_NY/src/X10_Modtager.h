#include <Arduino.h>


class X10_Modtager
{
public:
   void initX10_modtager(int rx_pin, int zero_pin);
   bool checkStartCode();
   byte checkHouseA();
   uint16_t checkUnit();
   uint16_t checkFunction();
   int* receiveCommands();
   void countOneZeroCross();
   void initZeroCrossInterrupt_Modtager();
   void initWaitTime();

private:
    int rx_pin_;
    int zero_pin_;
};

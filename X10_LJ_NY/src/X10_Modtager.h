#include <Arduino.h>


class X10_Modtager
{
public:
   void initX10_modtager(int rx_pin, int zero_pin);
   bool checkStartCode();
   bool checkHouseA();
   bool checkUnit();
   bool checkUnitSuffix();
   uint16_t checkFunction();
   int receiveCommands();
   void countOneZeroCross();
   void initZeroCrossInterrupt_Modtager();
   void initWaitTime();


private:
    int rx_pin_;
    int zero_pin_;
    uint8_t rollingByteStart_;
    uint8_t rollingByteHouse_;
    uint8_t rollingByteUnit_;
    uint8_t rollingByteSuffixUnit_;
    uint16_t rollingByteFunction_;
};

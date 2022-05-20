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
   int* receiveCommands(int UNIT);
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
    byte my_Unit_Array[3]{0b01101001,0b10101001,0b01011001};
};

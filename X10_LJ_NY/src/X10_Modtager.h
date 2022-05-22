#include <Arduino.h>


class X10_Modtager
{
public:
   void initX10_modtager(int rx_pin);
   bool checkStartCode();
   bool checkHouseA();
   bool checkUnit();
   bool checkUnitSuffix();
   bool checkFunctionSuffix();
   bool checkFunction();
   int* receiveCommands(int unit, int function);
   void countOneZeroCross();
   void initZeroCrossInterrupt_Modtager();

private:
    int rx_pin_;
    uint8_t rollingByteStart_;
    uint8_t rollingByteHouse_;
    uint8_t rollingByteUnit_;
    uint8_t rollingByteSuffixUnit_;
    uint8_t rollingByteFunction_;
    uint8_t rollingByteSuffixFunction_;
    uint8_t unit_Array[3]{0b01101001,0b10101001,0b01011001};
    uint8_t function_Array[2]{0b01011001,0b01011010}; //On/OFF
};

#include <Arduino.h>


class X10_Modtager
{
public:
   void initX10_modtager(int rx_pin, int unit);
   bool checkStartCode();
   bool checkHouseA();
   bool checkUnit();
   bool checkSuffix(int Suffix);
   bool checkFunction();
   int* receiveCommands();
   void countOneZeroCross();
   void initZeroCrossInterrupt_Modtager();
   void readingWait();
   

private:
    int rx_pin_;
    int unit_;
    uint8_t rollingByteStart_;
    uint8_t rollingByteHouse_;
    uint8_t rollingByteUnit_;
    uint8_t rollingByteSuffix_;
    uint8_t rollingByteFunction_;
    byte unit_Array[6]{0x69,0xA9,0x59,0x99,0x56,0x96}; //Unit 1 til 6
    byte function_Array[2]{0x59, 0x5A}; //Funktion: On, Off
    byte suffix_Array[2]{0b01, 0b10}; //Unit og Funktion
};

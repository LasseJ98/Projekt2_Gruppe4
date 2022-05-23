#include <Arduino.h>


class X10_Modtager
{
public:
   void initX10_modtager(int rx_pin);
   bool checkStartCode();
   bool checkHouseA();
   bool checkUnit();
   bool checkSuffix(int Suffix);
   bool checkFunction();
   int* receiveCommands(int unit, int function);
   void countOneZeroCross();
   void initZeroCrossInterrupt_Modtager();
   void readingWait();

private:
    int rx_pin_;
    uint8_t rollingByteStart_;
    uint8_t rollingByteHouse_;
    uint8_t rollingByteUnit_;
    uint8_t rollingByteSuffix_;
    uint8_t rollingByteFunction_;
    byte unit_Array[6]{0b01101001,0b10101001,0b01011001, 0b10011001, 0b01010110, 0b10010110}; //Unit 1 til 6
    byte function_Array[4]{0b01011001, 0b01011010, 0b01100110, 0b01100101}; //Funktion: On, Off, Bright, Dim
    byte suffix_Array[2]{0b01, 0b10}; //Unit og Funktion
};

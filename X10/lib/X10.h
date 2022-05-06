#include <Arduino.h>

class X10
{
public:
void initX10(int tx_pin, int zero_pin, int burst_pin);
void countZeroCross(int count);
void sendCommand(byte House_code,byte Unit, byte Function);
void sendStartCode();
void sendHouseA();
void sendFunction();
void sendUnit(int unit_Array);

private:
int tx_pin_;
int zero_pin_;
int burst_pin;
int unit_Array[3]{0b0110100101,0b1010100101,0b0101100101};
};
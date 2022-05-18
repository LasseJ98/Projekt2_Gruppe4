#include <Arduino.h>

class X10_Sender
{
public:
void initX10(int tx_pin, int zero_pin, int burst_pin);
void countZeroCross(int count);
void sendCommand(int Unit, int Function);
void sendStartCode();
void sendHouseA();
void sendFunction(int function);
void sendUnit(int unit_Array);
void countOneZeroCross();
void initZeroCrossInterrupt_Sender();
void burstTimerStart();
void sendSuffixUnit();
void sendSuffixFunction();

private:
int tx_pin_;
int zero_pin_;
int burst_pin_;
uint16_t unit_Array[3]{0b0110100101,0b1010100101,0b0101100101};
int function_Array[2]{0b0101100110,0b0101101010};
};


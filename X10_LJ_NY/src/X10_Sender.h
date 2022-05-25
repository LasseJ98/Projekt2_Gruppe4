#include <Arduino.h>

class X10_Sender
{
public:
void initX10(int tx_pin);
void sendCommand(int Unit, int Function);
void sendStartCode();
void sendHouseA();
void sendFunction(int function);
void sendUnit(int unit_Array);
void countOneZeroCross();
void initZeroCrossInterrupt_Sender();
void burstTimerStart();
void sendSuffix(int suffix);
void sendMorningRoutine();
void configMorning(int unit1, int function1, int unit2, int function2, int unit3, int function3, int unit4, int function4, int unit5, int function5, int unit6, int function6);
void sendEveningRoutine();
void configEveningRoutine(int unit1, int function1, int unit2, int function2, int unit3, int function3, int unit4, int function4, int unit5, int function5, int unit6, int function6);
void waitTime(int hour, int minutes);

private:
int tx_pin_;
byte unit_Array[6]{0b01101001,0b10101001,0b01011001, 0b10011001, 0b01010110, 0b10010110}; //Unit 1 til 6
byte function_Array[2]{0b01011001, 0b01011010}; //Funktion: On, Off, Dim
byte suffix_Array[2]{0b01, 0b10}; //Unit og Funktion

int morningDevice1;
int morningDevice2; 
int morningDevice3;
int morningDevice4;
int morningDevice5;
int morningDevice6;

int morningFunction1;
int morningFunction2;
int morningFunction3;
int morningFunction4;
int morningFunction5;
int morningFunction6;

int eveningDevice1;
int eveningDevice2;
int eveningDevice3;
int eveningDevice4;
int eveningDevice5;
int eveningDevice6;

int eveningFunction1;
int eveningFunction2;
int eveningFunction3;
int eveningFunction4;
int eveningFunction5;
int eveningFunction6;
};


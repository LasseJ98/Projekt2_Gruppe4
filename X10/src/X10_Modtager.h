#include <Arduino.h>
#include <X10_Sender.h>

class X10_Modtager : public X10_Sender
{
public:
   void initX10_modtager(int rx_pin, int zero_pin);
   bool checkStartCode();
   byte checkHouseA(byte rx_pin);
   uint16_t checkUnit(byte rx_pin);
   uint16_t checkFunction(byte rx_pin);
   void receiveCommands();

private:
    int rx_pin_;
    int zero_pin_;
};

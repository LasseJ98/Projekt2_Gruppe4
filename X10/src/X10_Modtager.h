#include <Arduino.h>
#include <X10_Sender.h>

class X10_Modtager : public X10_Sender
{
public:
   void initX10_modtager(int rx_pin, int zero_pin);
   bool checkStartCode();
   byte checkHouseA();
   uint16_t checkUnit();
   uint16_t checkFunction();
   int receiveCommands();

private:
    int rx_pin_;
    int zero_pin_;
};

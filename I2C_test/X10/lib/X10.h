#pragma once

class X10
{
public:
void initX10(int tx_pin, int rx_pin, int zero_pin);
void countZeroCross(int count);
void sendCommand(byte House_code,byte Unit, byte Function);

private:
int tx_pin_;
int zero_pin_;
}
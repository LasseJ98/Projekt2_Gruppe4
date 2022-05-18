#include "led.h"
#include "Arduino.h"

Led::Led(int dutyCycle)
{
    setPWM(dutyCycle);
}

void Led::setPWM(int dutyCycle)
{
    if(dutyCycle >= 0 && dutyCycle <= 100)
    {
        pwm_ = map(dutyCycle, 0, 100, 0, 255);
        analogWrite(3, pwm_);
    }

}

void Led::init()
{
    pinMode(3, OUTPUT);
    analogWrite(3, LOW);
}

bool Led::state(bool )
{

}
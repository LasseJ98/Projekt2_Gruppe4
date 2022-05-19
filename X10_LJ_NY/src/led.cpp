#include "Led.h"
#include "Arduino.h"

//Defining commands from  AN236 X10 Protocol
#define ON_COMMAND 0b00101
#define OFF_COMMAND 0b00111
#define DIM_COMMAND 0b01001
#define BRIGHT_COMMAND 0b01011
//Defining PWM values for different brightness. Values from 0% to 100%
#define ON_PWM 100
#define OFF_PWM 0
#define DIM_PWM 30
#define BRIGHT_PWM 80

Led::Led(int pin)
{
    init(pin);
}

void Led::setPWM(int dutyCycle)
{
    //Checks if the dutycycle is valid
    if(dutyCycle >= 0 && dutyCycle <= 100)
    {
        //Maps the 0-100 range to 0-255 range
        pwm_ = map(dutyCycle, 0, 100, 0, 255);
        analogWrite(pin_, pwm_);
    }

}

Led & Led::chooseBrightness(int command)
{
    //Takes 4 different corresponding to brightness and on off states
    //If the code is false, an error message is thrown
    switch (command)
    {
    case ON_COMMAND:
        setPWM(ON_PWM);
        break;
    case OFF_COMMAND:
        setPWM(OFF_PWM);
        break;
    case DIM_COMMAND:
        setPWM(DIM_PWM);
        break;
    case BRIGHT_COMMAND:
        setPWM(BRIGHT_COMMAND);
        break;
    default:
        Serial.print("\nCommmando ikke genkendt.\n");
        break;
    }

}

void Led::init(int pin)
{
    //Pin validation. Ensures that pin is suitable for PWM operation
    pin_ = ((pin >= 2 && pin <= 13) || (pin >= 44 && pin <= 46)
            ? pin : 0);

    //Pin output, then turns it off
    pinMode(pin_, OUTPUT);
    analogWrite(pin_, LOW);
}

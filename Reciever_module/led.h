
class Led
{
    public:
    Led(int pin);
    
    void init(int pin);
    void setPWM(int dutyCycle);
    Led & chooseBrightness(int command);

    private:
    int pwm_;
    int pin_;

};
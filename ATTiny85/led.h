
class Led
{
    public:
    Led(int = 100);
    
    void init();
    void setPWM(int);
    bool state(bool);

    private:
    int pwm_;
    bool state_;
};
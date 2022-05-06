#pragma once
using namespace std;

class ControlManually
{
public:
    ControlManually();
    void outputInit();
    void outputOn();
    void outputOff();
    void curtainInit();
    void curtainOpen();
    void curtainClose();
    void valveInit();
    void valveOpen();
    void valveClose();
    void soundInit();
    void soundOn();
    void soundOff();
    void doorInit();
    void doorLock();
    void doorUnlock();
    void tvInit();
    void tvOn();
    void tvOff();
    void lightInit();
    void lightControl(int PWM);
    void updateUI(int controlManual);
    void updateUIDoor(bool lockStatus);
    void updateUISound(bool soundStatus);
    void updateUIWatertank(bool valveStatus);
    void updateUILight(int PWM);
    void updateUITV(bool TVStatus);
    void updateUICurtain(bool curtainStatus);

private:
    int controlManual_;
    int PWM_;
    bool lockStatus_;
    bool soundStatus_;
    bool valveStatus_;
    bool TVStatus_;
    bool curtainStatus_;
};
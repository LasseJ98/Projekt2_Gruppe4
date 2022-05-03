#pragma once
using namespace std;

class StartMorningRoutine
{
public:
    StartMorningRoutine();
    void outputInit() const;
    void outputStartMorning() const;
    void curtainMorning() const;
    void soundMorning() const;
    void lightMorning() const;
    void valveMorning() const;

private:
    int time_;
};

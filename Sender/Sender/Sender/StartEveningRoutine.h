#pragma once
using namespace std;

class StartEveningRoutine
{
public:
    StartEveningRoutine();
    void outputInit();
    void outputEvening() const;
    void curtainEvening() const;
    void TVEvening() const;
    void soundEvening() const;
    void doorEvening() const;
    void lightEvening() const;

private:
    int time_;
};

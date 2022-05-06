#pragma once
using namespace std;

class ConfigureSystem
{
public:
    ConfigureSystem();
    void inputConfigureParameters();
    void saveParameters();
    void inputCode();
    void validateCode() const;
    void chooseRoutine();
    void updateUI();

private:
    int correctCode_;
};

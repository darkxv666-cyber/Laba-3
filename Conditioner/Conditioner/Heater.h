#pragma once
#include "HouseholdDevice.h"

class Heater : public HouseholdDevice {
public:
    Heater();
    Heater(const std::string& brand, const std::string& model,
        double weight, int power, int year,
        int temperature = 20, int mode = 1);

    void setTemperature(int temperature);
    void setMode(int mode);
    int getTemperature() const;
    int getMode() const;

    virtual void control(int temperature) override;
    virtual void printInfo() const override;

private:
    int temperature_;
    int mode_;
};
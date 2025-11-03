#include "Heater.h"
#include <iostream>

Heater::Heater() : HouseholdDevice(), temperature_(20), mode_(1) {}

Heater::Heater(const std::string& brand, const std::string& model,
    double weight, int power, int year,
    int temperature, int mode)
    : HouseholdDevice(brand, model, weight, power, year),
    temperature_(temperature), mode_(mode) {
}

void Heater::setTemperature(int temperature) { temperature_ = temperature; }
void Heater::setMode(int mode) { mode_ = mode; }
int Heater::getTemperature() const { return temperature_; }
int Heater::getMode() const { return mode_; }

void Heater::control(int temperature) {
    if (temperature > 45) {
        std::cout << "Температура слишком высокая! Обогреватель выключается." << std::endl;
        isOn_ = false;
        return;
    }

    temperature_ = temperature;
    if (temperature < 25) mode_ = 1;
    else if (temperature < 35) mode_ = 2;
    else mode_ = 3;

    std::cout << "Обогреватель настроен на температуру " << temperature
        << "°C (режим " << mode_ << ")" << std::endl;
}

void Heater::printInfo() const {
    HouseholdDevice::printInfo();
    if (isOn_) {
        std::cout << "Температура: " << temperature_ << "°C"
            << "\nРежим нагрева: " << mode_ << std::endl;
    }
}
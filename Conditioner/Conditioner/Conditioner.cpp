#pragma once
#include "HouseholdDevice.h"
#include <vector>
#include <string>

class Conditioner : public HouseholdDevice {
public:
    Conditioner();
    Conditioner(const std::string& brand, const std::string& model,
        double weight, int power, int year,
        int temperature = 25, const std::string& mode = "авто");

    void setTemperature(int temperature);
    void setMode(const std::string& mode);
    int getTemperature() const;
    std::string getMode() const;

    virtual void control(int temperature) override;
    void adjust(const std::string& newMode, int newTemperature = -1);
    double averageTemperatureChange() const;

    void serialize() const;
    void serialize(const std::string& filename) const;
    void deserialize();
    void deserialize(const std::string& filename);

    virtual void printInfo() const override;

private:
    int temperature_;
    std::string mode_;
    std::vector<int> temperatureHistory_;
};
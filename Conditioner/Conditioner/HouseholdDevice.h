#pragma once
#include <string>
#include "IControllable.h"

class HouseholdDevice : public IControllable {
public:
    HouseholdDevice();
    HouseholdDevice(const std::string& brand, const std::string& model,
        double weight, int power, int year);

    virtual ~HouseholdDevice() = default;

    void setBrand(const std::string& brand);
    void setModel(const std::string& model);
    void setWeight(double weight);
    void setPower(int power);
    void setYear(int year);

    std::string getBrand() const;
    std::string getModel() const;
    double getWeight() const;
    int getPower() const;
    int getYear() const;

    virtual void printInfo() const;

protected:
    std::string brand_;
    std::string model_;
    double weight_;
    int power_;
    int year_;
    bool isOn_;
};
#include "HouseholdDevice.h"
#include <iostream>

HouseholdDevice::HouseholdDevice()
    : brand_(""), model_(""), weight_(0), power_(0), year_(2023), isOn_(true) {
}

HouseholdDevice::HouseholdDevice(const std::string& brand, const std::string& model,
    double weight, int power, int year)
    : brand_(brand), model_(model), weight_(weight), power_(power),
    year_(year), isOn_(true) {
}

void HouseholdDevice::setBrand(const std::string& brand) { brand_ = brand; }
void HouseholdDevice::setModel(const std::string& model) { model_ = model; }
void HouseholdDevice::setWeight(double weight) { weight_ = weight; }
void HouseholdDevice::setPower(int power) { power_ = power; }
void HouseholdDevice::setYear(int year) { year_ = year; }

std::string HouseholdDevice::getBrand() const { return brand_; }
std::string HouseholdDevice::getModel() const { return model_; }
double HouseholdDevice::getWeight() const { return weight_; }
int HouseholdDevice::getPower() const { return power_; }
int HouseholdDevice::getYear() const { return year_; }

void HouseholdDevice::printInfo() const {
    std::cout << "Устройство: " << brand_ << " " << model_
        << "\nВес: " << weight_ << " кг"
        << "\nМощность: " << power_ << " Вт"
        << "\nГод выпуска: " << year_
        << "\nСостояние: " << (isOn_ ? "включено" : "выключено") << std::endl;
}
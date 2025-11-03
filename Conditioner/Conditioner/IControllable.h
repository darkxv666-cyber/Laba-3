#pragma once
class IControllable {
public:
    virtual void control(int temperature) = 0;
    virtual ~IControllable() = default;
};
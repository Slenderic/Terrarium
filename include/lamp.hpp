#ifndef LAMP_HPP
#define LAMP_HPP

#include "actuator.hpp"

class Lamp: public Actuator{
public:
    Lamp();
    Lamp(uint8_t pin);
    virtual ~Lamp() override;
    virtual void update(uint8_t val1) override;
};

#endif // LAMP_HPP
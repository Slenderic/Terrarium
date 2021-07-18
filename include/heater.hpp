#ifndef HEATER_HPP
#define HEATER_HPP

#include "actuator.hpp"

class Heater: public Actuator{
public:
    Heater();
    /** TODO: add Time limit */
    Heater(uint8_t pin);
    virtual ~Heater() override;
    virtual void update(uint8_t val1) override;
};

#endif // HEATER_HPP
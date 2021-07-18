#ifndef TSIC20X_HPP
#define TSIC20X_HPP

#include <TSIC.h>
#include "sensor.hpp"

class Tsic20x:public Sensor{
public:
    Tsic20x(void);
    Tsic20x(uint8_t signal_pin, uint8_t vcc_pin=255);
    virtual ~Tsic20x();
    virtual void update(void) override;
private:
    TSIC sensor;
};

#endif // TSIC20X_HPP
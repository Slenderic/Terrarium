#include <actuator.hpp>

Actuator::Actuator()
{
    
}
    
Actuator::Actuator(uint8_t pin, ACTU _role):
    actuatorPin(pin),
    role(_role)
{

}

Actuator::~Actuator()
{
    
}

void Actuator::update(uint8_t val)
{

}

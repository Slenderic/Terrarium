#include "lamp.hpp"

Lamp::Lamp()
{

}

Lamp::Lamp(uint8_t pin):
 Actuator(pin, ACTU::LAMP)
{

}

Lamp::~Lamp()
{

}

void Lamp::update(uint8_t val1){

}
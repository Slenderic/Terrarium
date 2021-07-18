#include "heater.hpp"

Heater::Heater()
{

}

Heater::Heater(uint8_t pin):
 Actuator(pin, ACTU::HEATER)
{

}

Heater::~Heater()
{
    //this->~Actuator();
}

void Heater::update(uint8_t val1){
    /** TODO: Make the scedual work **/
    //uint8_t placeholder;
    /*if((placeholder < scedual(ON)) && (placeholder > scedual(OFF))){
    this->switchOff();
    }else{
    this->switchOn();
    }*/
    /** TODO: Make Temperature coordination work **/
}

#include "tsic20x.hpp"

Tsic20x::Tsic20x(void)
{

}

Tsic20x::Tsic20x(uint8_t signal_pin, uint8_t vcc_pin):
    Sensor()
{
    TSIC temp(signal_pin,vcc_pin);
    this->sensor = temp;

}

Tsic20x::~Tsic20x()
{
    
}

void Tsic20x::update(void)
{
    sensType result;
    uint16_t temperature = 0;
    this->setPrevious();
    if (sensor.getTemperature(&temperature)) {
    result.push_back(sensor.calc_Celsius(&temperature));
    
    }else{
      result.push_back(255);
    }
#ifdef DEBUG
  Serial.print("Results TSIC T:");
  Serial.println(result[0]);
#endif
    this->setCurrent(result);
}
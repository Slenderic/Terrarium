#include "sensor.hpp"

Sensor::Sensor(){

}

Sensor::Sensor(SENS _role):
    role(_role)
{
  
}

Sensor::~Sensor(){
}
    
void Sensor::update(void){
    Serial.println("Not overriden"); 
}

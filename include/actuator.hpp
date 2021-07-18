#ifndef ACTUATOR_HPP
#define ACTUATOR_HPP

#include <properties.hpp>


class Actuator{
public:
    Actuator();
    Actuator(uint8_t pin, ACTU _role);
    virtual ~Actuator();

    virtual void update(uint8_t val);

    void switchOn(){digitalWrite(actuatorPin, HIGH);}
    void switchOff(){digitalWrite(actuatorPin, LOW);}

    ACTU getRole(void){return role;}
    
    void setScedual(Scedual s){scedual=s;}
    Scedual getScedual(void){return scedual;}
private:
    uint8_t actuatorPin = 0;
    ACTU role;
    Scedual scedual;
};

#endif // ACTUATORS_HPP
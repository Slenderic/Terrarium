#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <properties.hpp>


class Sensor{
public:
    Sensor();
    Sensor(SENS _role);
    virtual ~Sensor();
    virtual void update(void);
    void setCurrent(sensType data){previous = current; current = data;}
    void setPrevious(void){previous = current;}
    sensType getCurrent(void){return current;}
    sensType getPrevioud(void){return previous;}
    SENS getRole(void){return role;}
private:
    sensType current;
    sensType previous;
    SENS role;
};

#endif // SENSOR_HPP
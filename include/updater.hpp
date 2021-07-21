#ifndef UPDATER_HPP
#define UPDATER_HPP

#include "sensor.hpp"
#include "actuator.hpp"
#include "rgb.hpp"

/** TODO: Solve problem with rgb.hpp : multiple inclusions of properties.hpp**/
class Updater{
public:
    Updater();
    ~Updater();
    void addActuator(std::shared_ptr<Actuator> actuator){v_actuator.push_back(actuator);}
    void addSensor(std::shared_ptr<Sensor> sensor){v_sensor.push_back(sensor);}
    void addLED(std::shared_ptr<RGB> led){v_led.push_back(led);}
    void update(void);
    void setTime(uint8_t time){_time = time;}
    uint8_t getTime(void){return _time;}
private:
    std::vector<std::shared_ptr<Actuator>> v_actuator;
    std::vector<std::shared_ptr<Sensor>> v_sensor;
    std::vector<std::shared_ptr<RGB>> v_led;
    uint8_t _time;
};

#endif //UPDATER_HPP
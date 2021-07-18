#include <updater.hpp>

Updater::Updater()
{

}

Updater::~Updater()
{

}

void Updater::update(void)
{
    uint8_t t = this->getTime();
#ifdef DEBUG
    Serial.print("Sensors ");
    Serial.println(v_sensor.size());
#endif

    /** TODO: Automate!!! **/
    if(v_sensor.size() > 0){
        for (auto i = 0; i < v_sensor.size(); i++)
        {
            v_sensor[i]->update();
            if(v_sensor[i]->getRole() == SENS::SHT15){
                /* code */
            }else if (v_sensor[i]->getRole() == SENS::TSIC201){
                /* code */
            }
            
        }
    }

    if(v_actuator.size() != 0){
        for (auto i = 0; i < v_actuator.size(); i++)
        {
            v_actuator[i]->update(t);
            if(v_actuator[i]->getRole() == ACTU::HEATER){
                
            }else if(v_actuator[i]->getRole() == ACTU::LAMP){

            }
        }
    }
    

}
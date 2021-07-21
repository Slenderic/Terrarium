#include "properties.hpp"
#include "heater.hpp"
#include "lamp.hpp"
#include "sht.hpp"
#include "tsic20x.hpp"
#include "updater.hpp"

std::shared_ptr<Updater> updater;
auto start = std::chrono::steady_clock::now();
auto end = std::chrono::steady_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;

uint8_t t = 0; //just for debuging

void setup() {
  updater = std::make_shared<Updater>();

  Serial.begin(115200);
  // Add Actuators
  updater->addActuator(std::make_shared<Heater>(HEATER_PIN));
  updater->addActuator(std::make_shared<Lamp>(LAMP_PIN));

  // Add Sensors
  //updater->addSensor(std::make_shared<SHT>(SHT_DATA,SHT_CLOCK,SHT_SUPPLY_1));
  updater->addSensor(std::make_shared<SHT>(SHT_DATA,SHT_CLOCK,SHT_SUPPLY_2));

  /** TODO: Change DATA pin TSIC pulls down if not supplied **/
  updater->addSensor(std::make_shared<Tsic20x>(TSIC_DATA_1,TSIC_SUPPLY));
  updater->addSensor(std::make_shared<Tsic20x>(TSIC_DATA_2,TSIC_SUPPLY));

  /** TODO: Set RGB **/
  updater->addLED(std::make_shared<RGB>(18, 0, LED::BLUE));
  updater->addLED(std::make_shared<RGB>(19, 1, LED::GREEN));
  updater->addLED(std::make_shared<RGB>(21, 2, LED::RED));

  /** TODO: Website implementation / Internet connection**/

}

void loop() {
  /** TODO: get time via websocket**/
  
  /** TODO: Set time as input var of update **/
  delay(50);
  end = std::chrono::steady_clock::now();
  elapsed_seconds = end-start;
  if(elapsed_seconds.count() >= 5){//update every five seconds
    t += 5;
    start = std::chrono::steady_clock::now();    
    updater->setTime(t);
    updater->update();

  }
}
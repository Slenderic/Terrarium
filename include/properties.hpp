#ifndef PROPERTIES_HPP
#define PROPERTIES_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <array>
#include <vector>
#include <math.h>
#include <chrono>
#include <thread>

#include <Arduino.h>

#define DEBUG 1

#define HEATER_PIN 25
#define LAMP_PIN 26

#define SHT_DATA 21
#define SHT_CLOCK 22
#define SHT_SUPPLY_1 19
#define SHT_SUPPLY_2 18

#define TSIC_DATA_1 4
#define TSIC_DATA_2 19
#define TSIC_SUPPLY 15

#define LED_G 

#define ON 0
#define OFF 1

/** Forward declaration **/
class Sensor;   
class Actuator;

enum LED {RED=0, GREEN, BLUE, UV}; 
enum class ACTU {LAMP=0, HEATER};
enum class SENS {SHT15=0, TSIC201}; //Definition of sensor can be extendet at will

using sensType = std::vector<float>;
using Scedual = std::vector<uint8_t>;

using v_sensor = std::vector<std::shared_ptr<Sensor>>;

#endif // PROPERTIES_HPP    
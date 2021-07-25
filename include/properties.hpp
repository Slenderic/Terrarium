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

#define LED_R_PIN 35
#define LED_G_PIN 34
#define LED_B_PIN 33
#define LED_UV_PIN 32

#define ON 0
#define OFF 1

/** Forward declaration **/
class Sensor;   
class Actuator;
class Heater;
class Lamp;
class RGB;

enum LED {RED=0, GREEN=1, BLUE=2, UV=3}; 
enum class ACTU {LAMP=0, HEATER};
enum class SENS {SHT15=0, TSIC201}; //Definition of sensor can be extendet at will


using sensType = std::vector<float>;
using Scedual = std::vector<uint8_t>;

using v_sensor = std::vector<std::shared_ptr<Sensor>>;

#endif // PROPERTIES_HPP    
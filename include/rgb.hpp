#ifndef RGB_HPP
#define RGB_HPP

#include <properties.hpp>

#define H2S 3600
#define PERIOD 1*H2S // just temp for testing

/** TODO: change ctor of rgb to accept the array of led Values**/

// unsigned char ledVal[4][12]=    {{0, 255, 255, 255, 255, 255, 255, 255, 244, 201,  64, 0},   //red
//                                     {0, 147, 197, 214, 241, 250, 255, 255, 240, 226, 156, 0},   //green
//                                     {0,  41, 143, 170, 224, 244, 251, 255, 255, 255, 255, 0},   //blue
//                                     {0,  80, 168, 210, 241, 255, 255, 241, 210, 168, 80, 0}};   //uv
class RGB{
public:
    RGB();
    RGB(uint8_t pin, uint8_t ch,LED led);
    virtual ~RGB();
    virtual void update(void);
    void setTime(uint8_t time){_t = time;}
    void setVal(uint8_t val){_val = val;}
    uint8_t getVal(){return _val;}
    uint8_t getTime(){return _t;}
private:
    uint8_t _val = 0;
    uint8_t _t = 0;
    uint8_t _pin = 0;
    uint8_t _ch;
    LED _led;
    char _ledVals[4][12];
};

#endif // RGB_HPP
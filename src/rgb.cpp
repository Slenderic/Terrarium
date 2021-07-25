#include "rgb.hpp"

RGB::RGB()
{

}

RGB::RGB(uint8_t pin, uint8_t ch, LED led):
    _pin(pin),
    _ch(ch),
    _led(led)
{
    ledcAttachPin(_pin,_ch);
}

RGB::~RGB(){

}

void RGB::update(void){
    // get Info to do the interpolation
    uint8_t windows = sizeof(_ledVals[_led])/sizeof(*_ledVals[_led]); //temp just to know how many values there are in the array
    uint8_t dt = PERIOD/windows;
    uint8_t indx = _t/dt;

    if(indx < (windows-1)){
        uint8_t dr = _ledVals[_led][indx+1]-_ledVals[_led][indx];
        float slope = dr/dt;
        uint8_t t = _t%dt;
        setVal(_ledVals[_led][indx]+slope*t);

    }else{
        setVal(0);// make it dark
    }

    ledcWrite(_ch,_val);
}
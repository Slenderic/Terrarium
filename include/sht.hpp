#ifndef SHT_HPP
#define SHT_HPP

#include <sensor.hpp>

#define	SHT_UNAVAIL  -32768
#define	SHT_CRC_FAIL -32767
#define SHT_VALID    -32000
#define SHT_MAX_TEMP  123.8
#define SHT_MIN_TEMP -40

class SHT: public Sensor{
  public:
    
    enum class Voltage : uint8_t
    {
      DC_5_0v = 0
      , DC_4_0v
      , DC_3_5v
      , DC_3_3v
      , DC_3_0v
      , DC_2_5v
    };

    enum class Resolution : uint8_t
    {
      High_Res = 0b0,
      Low_Res  = 0B1 
    };
    
    enum class ShtCommand : uint8_t
    {
      MeasureTemperature        = 0b00000011,
      MeasureRelativeHumidity = 0b00000101,
      ReadStatusRegister      = 0b00000111,
      WriteStatusRegister     = 0b00000110,
      SoftReset               = 0b00011110
    };

    SHT(uint8_t dataPin, uint8_t clockPin, int8_t supplyPin = -1, Voltage voltage = Voltage::DC_3_3v, Resolution resolution = Resolution::High_Res);
    //SHT(uint8_t dataPin, uint8_t clockPin, Voltage voltage = Voltage::DC_3_3v, Resolution resolution = Resolution::High_Res);
    virtual ~SHT() override; 

    void update(void) override;

    float getTemperatureC(void) const {return _tempC;} 
    float getTemperatureF(void) const {return _tempF;} 
    float getHumidity(void) const {return _humidity;}


  private:
    void setTemperatureC(float tempC) {this->_tempC = tempC;}
    void setTemperatureF(float tempF) {this->_tempF = tempF;} 
    void setHumidity(float humidity) {this->_humidity = humidity;}

    void readTemperatureC(void);
    void readTemperatureF(void);
    void readHumidity(void);

    bool shtReady(void) const;
    uint16_t result(void) const;

    void startTransmission(void) const;
    uint16_t readRawData(void) const;
    bool sendCommand(ShtCommand command) const;

    void initalizeSensor(void) const;

    double getC1(Resolution resolution) const;
    double getC2(Resolution resolution) const;
    double getC3(Resolution resolution) const;

    double getT1(Resolution resolution) const;
    double getT2(Resolution resolution) const;

    double getD1C(Voltage voltage) const;
    double getD2C(Resolution resolution) const;

    double getD1F(Voltage voltage) const;
    double getD2F(Resolution resolution) const;

    void delay_sht(void) const{ delayMicroseconds(50); }

    void scl_out() const      { pinMode(_clockPin, OUTPUT); }
    void scl_hi() const       { digitalWrite(_clockPin, HIGH); }
    void scl_lo() const       { digitalWrite(_clockPin, LOW); }
    void sda_hi() const       { digitalWrite(_dataPin, HIGH); }
    void sda_lo() const       { digitalWrite(_dataPin, LOW); }
    void sda_out() const      { pinMode(_dataPin, OUTPUT); sda_hi();}
    void sda_in() const       { pinMode(_dataPin, INPUT_PULLUP);}
    void scl_pulse() const    { scl_out(); scl_hi(); delay_sht(); scl_lo(); }
    uint8_t	sda_val() const   { sda_in(); return digitalRead(_dataPin);}

    const uint8_t _dataPin;
    const uint8_t _clockPin;
    const int8_t _supplyPin;

    const Voltage _voltage;
    const Resolution _resolution;

    float _tempC = 0;
    float _tempF = 0;
    float _humidity = 0;
};

#endif // SHT_HPP
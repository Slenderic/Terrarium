/**
 * 
 * 
 * 
 * 
 */

#include "sht.hpp"

/* =========== ctors =========== */
SHT::SHT(uint8_t dataPin, uint8_t clockPin, int8_t supplyPin, Voltage voltage, Resolution resolution):
_dataPin{dataPin},
_clockPin{clockPin},
_supplyPin{supplyPin},
_voltage{voltage},
_resolution{resolution}
{
  if(supplyPin > 0)
    pinMode(supplyPin, OUTPUT);
  this->initalizeSensor();
}

/*SHT::SHT(uint8_t dataPin, uint8_t clockPin, Voltage voltage, Resolution resolution):
_dataPin{dataPin},
_clockPin{clockPin},
_supplyPin{-1},
_voltage{voltage},
_resolution{resolution}
{
  this->initalizeSensor();
}*/

/* =========== dtors =========== */
SHT::~SHT(){
  
}


/* =========== Public Methodes =========== */
void SHT::update(void)
{
  sensType result;
  if(_supplyPin != -1)
      this->initalizeSensor();
    
  delay(5);
  this->readTemperatureC();
  delay(5);
  this->readHumidity();
  delay(5);
  if(_supplyPin != -1)
    digitalWrite(_supplyPin, LOW);
  result.push_back(this->getTemperatureC());
  result.push_back(this->getHumidity());

#ifdef DEBUG
  Serial.print("Results SHT T:");
  Serial.print(result[0]);
  Serial.print(" H: ");
  Serial.println(result[1]);
#endif
  this->setCurrent(result);
/** TODO:  return status (no connextion, waitng ect) */
  /*if(this->_tempC >= SHT_MAX_TEMP || this->_tempC <= SHT_MIN_TEMP)
    return false;
  else
    return true; 
    
  if(this->_humidity >= 100 || this->_humidity <= 0)
    return false;
  else
    return true; */

}

/* =========== Private Methodes =========== */
void SHT::readTemperatureC(void) 
{
    uint16_t v = 0;
    const double D1 = getD1C(_voltage);
    const double D2 = getD2C(_resolution);
    
    this->startTransmission();
    bool ack = this->sendCommand(ShtCommand::MeasureTemperature);

    if(!ack){
        while (this->sda_val());
        v = this->result();
        if(v > SHT_VALID){
            this->setTemperatureC(D1+D2*v);
        }        
    }
}

/** DO IT YOURSELF **/
void SHT::readTemperatureF(void)
{
}

void SHT::readHumidity(void)
{
    uint16_t v = 0;
    float rhLin = 0;
    const double C1 = getC1(_resolution);
    const double C2 = getC2(_resolution);
    const double C3 = getC3(_resolution);
    const double T1 = getT1(_resolution);
    const double T2 = getT2(_resolution);
    
    this->startTransmission();
    bool ack = this->sendCommand(ShtCommand::MeasureRelativeHumidity);
    if(!ack){
        while (this->sda_val());
        v = this->result();
        rhLin = C1 + C2*v + C3*v*v; 
        this->setHumidity((this->getTemperatureC()-25)*(T1+T2*v)+rhLin);
               
    }
}

bool SHT::shtReady(void) const
{
    sda_in();
    return sda_val() == 0;
}

uint16_t SHT::result(void) const
{
    if(!this->shtReady())
        return -1;
    int v = this->readRawData() << 8;
    v |= this->readRawData();
    /** TODO: Cecksum **/
    //int checksum = this->readRawData();
    return v;
}

void SHT::startTransmission(void) const
{
    this->sda_in();
    this->sda_out();
    this->scl_hi();
    this->sda_lo();this->delay_sht();
    this->scl_lo();this->delay_sht();
    this->scl_hi();this->delay_sht();
    this->sda_hi();
    this->scl_lo();this->delay_sht();
}

uint16_t SHT::readRawData(void) const
{
    this->sda_in();
    uint16_t  b = 0;

    /** MSB **/
    for(uint8_t i = 0; i < 8; i++)
    {
        b <<= 1;
        if(this->sda_val())
            b |= 1;
        this->scl_pulse();
        this->delay_sht();
    }
    // lo ack
    this->sda_out();
    this->sda_lo();
    this->delay_sht();
    this->scl_pulse();
    this->sda_hi();
    this->delay_sht();


    return b;
}

bool SHT::sendCommand(ShtCommand command) const
{
    /** TODO: checksum **/
    uint8_t b = static_cast<uint8_t>(command);
    this->sda_out();

    for(uint8_t i = 0; i < 8; i++)
    {
        if(b & 0x80)
            this->sda_hi();
        else
            this->sda_lo();
        b <<= 1;
        this->delay_sht();
        this->scl_pulse();        
    }
    
    //ack
    this->sda_in();
    bool ack = this->sda_val();
    this->scl_pulse();
    return ack;
}

void SHT::initalizeSensor(void) const
{
    
    if (_supplyPin == -1)
    {
        this->startTransmission();
        this->sendCommand(ShtCommand::SoftReset);
        delay(11);

        this->startTransmission();
        this->sendCommand(ShtCommand::WriteStatusRegister);
        this->sendCommand(static_cast<ShtCommand>(_resolution));
    }else
    {
        digitalWrite(_supplyPin, HIGH);

        this->startTransmission();
        this->sendCommand(ShtCommand::SoftReset);
        delay(11);

        this->startTransmission();
        this->sendCommand(ShtCommand::WriteStatusRegister);
        this->sendCommand(static_cast<ShtCommand>(_resolution));
        
    }
    
    
}

double SHT::getC1(Resolution resolution) const
{
    const double VALUES[] = {
                            -2.0468,    // 12 bit
                            -2.0468     // 8 bit
                          };
  return VALUES[static_cast<uint8_t>(resolution)];
}

double SHT::getC2(Resolution resolution) const
{
  const double VALUES[] = {
                            0.0367,     // 12 bit
                            0.5872      // 8 bit
                          };

  return VALUES[static_cast<uint8_t>(resolution)];
}

double SHT::getC3(Resolution resolution) const
{
  const double VALUES[] = {
                            -1.5955e-6,     // 12 bit
                            -4.0845e-4      // 8 bit
                          };

  return VALUES[static_cast<uint8_t>(resolution)];
}

double SHT::getT1(Resolution resolution) const
{
  const double VALUES[] = {
                            0.01,       // 12 bit
                            0.01        // 8 bit
                          };

  return VALUES[static_cast<uint8_t>(resolution)];
}

double SHT::getT2(Resolution resolution) const
{
  const double VALUES[] = {
                            0.00008,    // 12 bit
                            0.00128     // 8 bit
                          };

  return VALUES[static_cast<uint8_t>(resolution)];
}

double SHT::getD1C(Voltage voltage) const
{
  const double VALUES[] = {
                            -40.1,      // 5.0v
                            -39.8,      // 4.0v
                            -39.7,      // 3.5v
                            -39.66,     // 3.3v, linear interpolation
                            -39.6,      // 3.0v
                            -39.4,      // 2.5v
                          };

  return VALUES[static_cast<uint8_t>(voltage)];
}

double SHT::getD2C(Resolution resolution) const
{
  const double VALUES[] = {
                            0.01,       // 14 bit
                            0.04        // 12 bit
                          };

  return VALUES[static_cast<uint8_t>(resolution)];
}

double SHT::getD1F(Voltage voltage) const
{
  const double VALUES[] = {
                            -40.2,      // 5.0v
                            -39.6,      // 4.0v
                            -39.5,      // 3.5v
                            -39.42,     // 3.3v, linear interpolation
                            -39.3,      // 3.0v
                            -38.9,      // 2.5v
                          };

  return VALUES[static_cast<uint8_t>(voltage)];
}

double SHT::getD2F(Resolution resolution) const
{
  const double VALUES[] = {
                            0.018,      // 14 bit
                            0.072       // 12 bit
                          };

  return VALUES[static_cast<uint8_t>(resolution)];
}
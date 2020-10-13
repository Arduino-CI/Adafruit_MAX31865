#include "Adafruit_MAX31865_CI.h"
#ifdef __AVR
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#endif

#include <stdlib.h>

Adafruit_MAX31865_CI::Adafruit_MAX31865_CI(int8_t spi_cs, int8_t spi_mosi,
                                     int8_t spi_miso, int8_t spi_clk)
    : Adafruit_MAX31865_Base(spi_cs, spi_mosi, spi_miso, spi_clk){}

Adafruit_MAX31865_CI::Adafruit_MAX31865_CI(int8_t spi_cs)
    : Adafruit_MAX31865_Base(spi_cs) {}
      

bool Adafruit_MAX31865_CI::begin(max31865_numwires_t wires) {
  Adafruit_MAX31865_Base::begin(wires);
  return true;
}

uint8_t Adafruit_MAX31865_CI::readFault(void) {
  return Adafruit_MAX31865_Base::readFault();
}

void Adafruit_MAX31865_CI::clearFault(void) {
  Adafruit_MAX31865_Base::clearFault();
}

void Adafruit_MAX31865_CI::enableBias(bool b) {
  Adafruit_MAX31865_Base::enableBias(b);
}

void Adafruit_MAX31865_CI::autoConvert(bool b) {
  Adafruit_MAX31865_Base::autoConvert(b);
}

void Adafruit_MAX31865_CI::enable50Hz(bool b) {
  Adafruit_MAX31865_Base::enable50Hz(b);
}

void Adafruit_MAX31865_CI::setWires(max31865_numwires_t wires) {
  Adafruit_MAX31865_Base::setWires(wires);
}


float Adafruit_MAX31865_CI::temperature(float RTDnominal, float refResistor) {
  return Adafruit_MAX31865_Base::temperature(RTDnominal, refResistor);
}

uint16_t Adafruit_MAX31865_CI::readRTD(void) {
  return Adafruit_MAX31865_Base::readRTD();
}



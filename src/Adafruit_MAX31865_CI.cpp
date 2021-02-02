#include "Adafruit_MAX31865_CI.h"
#ifdef MOCK_PINS_COUNT
#ifdef __AVR
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#endif

#include <stdlib.h>

Adafruit_MAX31865_CI::Adafruit_MAX31865_CI(int8_t spi_cs, int8_t spi_mosi,
                                           int8_t spi_miso, int8_t spi_clk)
    : Adafruit_MAX31865_Base(spi_cs, spi_mosi, spi_miso, spi_clk) {}

Adafruit_MAX31865_CI::Adafruit_MAX31865_CI(int8_t spi_cs)
    : Adafruit_MAX31865_Base(spi_cs) {}

bool Adafruit_MAX31865_CI::begin(max31865_numwires_t wires) {
  return Adafruit_MAX31865_Base::begin(wires);
}

// BAD: see https://github.com/Arduino-CI/Adafruit_MAX31865/issues/7
float Adafruit_MAX31865_CI::temperature(float RTDnominal, float refResistor) {
  return Adafruit_MAX31865_Base::temperature(RTDnominal, refResistor);
}

#endif

#pragma once
#include <Adafruit_MAX31865.h>
#ifdef ARDUINO_CI

/*! Interface class for the MAX31865 RTD Sensor reader */
class Adafruit_MAX31865_CI : Adafruit_MAX31865_Base {
public:
  Adafruit_MAX31865_CI(int8_t spi_cs, int8_t spi_mosi, int8_t spi_miso,
                    int8_t spi_clk);
  Adafruit_MAX31865_CI(int8_t spi_cs);

  bool begin(max31865_numwires_t x = MAX31865_2WIRE);

  uint8_t readFault(void);
  void clearFault(void);
  uint16_t readRTD();

  void setWires(max31865_numwires_t wires);
  void autoConvert(bool b);
  void enable50Hz(bool b);
  void enableBias(bool b);

  float temperature(float RTDnominal, float refResistor);

  virtual String className() const { return "Adafruit_MAX3186_CI"; }
};

#endif

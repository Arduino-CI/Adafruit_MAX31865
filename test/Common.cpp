#include <bitset>
#include <iostream>
#include <vector>

#include "Arduino.h"
#include "ArduinoUnitTests.h"
#include "Adafruit_MAX31865_CI.h"

unittest(begin) {
  //Implementation Not Finnished
  vector<int> expected{};
  Adafruit_MAX31865_Test thermo(d4, d5, d6, d7);
  bool testBegin = thermo.begin(MAX31865_3WIRE);
  assertTrue(testBegin);

}

unittest(readRTD) {
  //Not Yet Implemented
  int expected = 0;
  Adafruit_MAX31865_Test thermo(d4, d5, d6, d7);
  thermo.begin(MAX31865_3WIRE);
  int testReadRTD = thermo.readRTD();
  assert(testReadRTD == expected);
}

unittest(get_temp) {
  float rref = 430.0;
  float rNominal = 100.0;
  float expectedTemperature = -242.02;
  Adafruit_MAX31865_Test thermo(d4, d5, d6, d7);
  thermo.begin(MAX31865_3WIRE);
  float testTemperature = thermo.temperature(rNominal, rref);
  assert(testTemperature == expectedTemperature);
}